#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

int getRand(int min, int max)
{
	return rand() % (max - min + 1) + min; 
}

int isEqual(int x, int y)
{
	return x == y;
}

int main()
{
	int seed = 1000;
    int numPlayer;
    int random, cardPos, itr, buysBefore, beforeDiscardCt;
    int i, j, p;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int beforeDeckCt[MAX_PLAYERS];
    int beforeHandCt[MAX_PLAYERS];
    int beforeSupplyCt[10];
    int handCtFail = 0;
    int deckCtFail = 0; 
    int buyCtFail = 0;
    int discardCtFail = 0;
    int supplyCtFail = 0;
    struct gameState G;
    srand(time(NULL));

    for(itr = 0; itr < 10000; itr++)
    {
	    numPlayer = getRand(2, MAX_PLAYERS);
	    memset(&G, 23, sizeof(struct gameState));
	    initializeGame(numPlayer, k, seed, &G);

	    for(i = 0; i < numPlayer; i++)
	    {
	 		//assign player random number of cards in deck and hand
	    	G.deckCount[i] = getRand(4, MAX_DECK);
	    	G.handCount[i] = getRand(1, MAX_HAND - 3);

	    	//add number to before array to keep track of values before adventurer is played
	    	beforeDeckCt[i] = G.deckCount[i];
	    	beforeHandCt[i] = G.handCount[i];

	    	//printf("Player %d deckCount: %d\n", i, G.deckCount[i]);
	    	//printf("Player %d handCount: %d\n", i, G.handCount[i]);

	    	for(j = 0; j < G.deckCount[i]; j++) //assign random kingdom and treasure cards to deck
	    	{
	    		random = getRand(0, 12);
	    		if(random == 10) { G.deck[i][j] = copper; }
	    		else if(random == 11) { G.deck[i][j] = silver; }
	    		else if(random == 12) { G.deck[i][j] = gold; }
	    		else { G.deck[i][j] = k[random]; }
	    	}

	    	for(j = 0; j < G.handCount[i]; j++) //assign random kingdom and treasure cards to hand
	    	{
	    		random = getRand(0, 12);
	    		if(random == 10) { G.hand[i][j] = copper; }
	    		else if(random == 11) { G.hand[i][j] = silver; }
	    		else if(random == 12) { G.hand[i][j] = gold; }
	    		else { G.hand[i][j] = k[random]; }
	    	}
	    }

	    //get supply count before playing card
	    for(i = 0; i < 10; i++)
	    {
	    	beforeSupplyCt[i] = G.supplyCount[k[i]];
	    }

	    p = getRand(0, numPlayer - 1); //get random player to play council room card
	    G.whoseTurn = p;
	    G.discardCount[p] = getRand(0, 50);
	    beforeDiscardCt = G.discardCount[p];
	    G.numBuys = getRand(1, 10);
	    buysBefore = G.numBuys;
	    

	    //ensure we have a council room card in player's hand
	    cardPos = -1;
	    for(i = 0; i < G.handCount[p]; i++)
	    {
	    	if(G.hand[p][i] == council_room)
	    	{
	    		cardPos = i;
	    	}
	    }

	    if(cardPos < 0) //if player does not have an council card, add it to their hand
	    {
	    	G.hand[p][0] = council_room;
	    	cardPos = 0;
	    }

	    //play council room card 
	    cardEffect(council_room, 0, 0, 0, &G, cardPos, 0);

	    //check hand count for player
	    if(!isEqual(beforeHandCt[p] + 3, G.handCount[p])) 
	    {
	    	//printf("Hand count gained 4 new cards for player: FAIL\n");
	    	handCtFail++;
	    }

	    //check deck count for player
	    if(!isEqual(beforeDeckCt[p] - 4, G.deckCount[p]))
	    {
	    	//printf("Deck count decreased by 4 for player: FAIL\n");
	    	deckCtFail++;
	    }

	    //check discard count is correct
	    if(!isEqual(beforeDiscardCt + 1, G.discardCount[p]))
	    {
	    	//printf("Discard count is correct after playing card: FAIL\n");
	    	discardCtFail++;
	    }

	    //check if number of buys added is correct
	    if(!isEqual(buysBefore + 1, G.numBuys))
	    {
	    	//printf("Number of buys for player increased by 1: FAIL\n");
	    	buyCtFail++;
	    }

	    //ensure deck count decreased by 1 and hand count increased by 1 for the other players
	    for(i = 0; i < numPlayer; i++)
	    {
	    	if(i != p)
	    	{
	    		if(!isEqual(beforeDeckCt[i] - 1, G.deckCount[i]))
	    		{
	    			//printf("Deck count for other players decreased by one: FAIL\n");
	    			deckCtFail++;
	    		}

	    		if(!isEqual(beforeHandCt[i] + 1, G.handCount[i]))
	    		{
	    			//printf("Hand count for other players increased by one: FAIL\n");
	    			handCtFail++;
	    		}
	    	}
	    }

	    //ensure supply count remains unaffected
	    for(i = 0; i < 10; i++)
	    {
	    	if(!isEqual(beforeSupplyCt[i], G.supplyCount[k[i]]))
	    	{
	    		//printf("Supply count remains unaffected: FAIL\n");
	    		supplyCtFail++;
	    	}
	    }
	}

	printf("\n\n");
	printf("Number of failures for player buy count: %d\n", buyCtFail);
	printf("Number of failures for hand count: %d\n", handCtFail);
	printf("Number of failures for deck count: %d\n", deckCtFail);
	printf("Number of failures for discard count after playing card: %d\n", discardCtFail);
	printf("Number of failures for supply count: %d\n", supplyCtFail);
	
    return 0;
}