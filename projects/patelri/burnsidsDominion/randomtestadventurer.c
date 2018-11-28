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
    int random, treasureCards, advenPos, after, itr;
    int i, j, p;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int beforeDeckCt[MAX_PLAYERS];
    int beforeHandCt[MAX_PLAYERS];
    int beforeSupplyCt[10];
    int handCtFail = 0;
    int deckCtFail = 0; 
    int treasureCtFail = 0;
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
	    	G.deckCount[i] = getRand(3, MAX_DECK);
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

	    //get supply count before playing adventurer card
	    for(i = 0; i < 10; i++)
	    {
	    	beforeSupplyCt[i] = G.supplyCount[k[i]];
	    }

	    p = getRand(0, numPlayer - 1); //get random player to play adventurer card
	    G.whoseTurn = p;

	    //ensure player has atleast 3 treasure cards in their deck
	    treasureCards = 0;
	    for(i = 0; i < G.deckCount[p]; i++)
	    {
	    	if(G.deck[p][i] == gold || G.deck[p][i] == silver || G.deck[p][i] == copper)
	    	{
	    		treasureCards++;
	    	}
	    }

	    if(treasureCards < 3) //if there are not enough treasure cards in deck, add them in
	    {
	    	G.deck[p][0] = gold;
	    	G.deck[p][1] = silver;
	    	G.deck[p][2] = copper;
	    }
	    

	    //ensure we have an adventurer card in player's hand
	    advenPos = -1;
	    for(i = 0; i < G.handCount[p]; i++)
	    {
	    	if(G.hand[p][i] == adventurer)
	    	{
	    		advenPos = i;
	    	}
	    }

	    if(advenPos < 0) //if player does not have an adventurer card, add it to their hand
	    {
	    	G.hand[p][0] = adventurer;
	    	advenPos = 0;
	    }

	    //get the count of treasure cards in player's hand before playing adventurer
	  	treasureCards = 0;
	    for(i = 0; i < G.handCount[p]; i++)
	    {
	    	if(G.hand[p][i] == gold || G.hand[p][i] == silver || G.hand[p][i] == copper)
	    	{
	    		treasureCards++;
	    	}
	    }

	    //play adventurer card 
	    cardEffect(adventurer, 0, 0, 0, &G, advenPos, 0);

	    //get count of treasure cards in player's hand after playing adventurer
	    after = 0;
	    for(i = 0; i < G.handCount[p]; i++)
	    {
	    	if(G.hand[p][i] == gold || G.hand[p][i] == silver || G.hand[p][i] == copper)
	    	{
	    		after++;
	    	}
	    }

	    if(!isEqual(treasureCards + 2, after)) //check if player gaines two additional cards in hand
	    {
	    	//printf("Gain 2 additional treasure cards to player hand: FAIL\n");
	    	treasureCtFail++;
	    }

	    //check hand count for player
	    if(!isEqual(beforeHandCt[p] + 2, G.handCount[p]))
	    {
	    	//printf("Hand count increased by two for player: FAIL\n");
	    	handCtFail++;
	    }

	    //check deck count for player
	    if((beforeDeckCt[p] - G.deckCount[p]) < 2)
	    {
	    	//printf("Deck count decreased by atleast 2 for player: FAIL\n");
	    	deckCtFail++;
	    }

	    //check discard count is correct
	    if(!isEqual(beforeDeckCt[p] - G.deckCount[p] - 2, G.discardCount[p]))
	    {
	    	//printf("Discard count is correct after playing card: FAIL\n");
	    	discardCtFail++;
	    }

	    //ensure deck count and hand count of other players remain unaffected
	    for(i = 0; i < numPlayer; i++)
	    {
	    	if(i != p)
	    	{
	    		if(!isEqual(beforeDeckCt[i], G.deckCount[i]))
	    		{
	    			//printf("Deck count for other player remain unaffected: FAIL\n");
	    			deckCtFail++;
	    		}

	    		if(!isEqual(beforeHandCt[i], G.handCount[i]))
	    		{
	    			//printf("Hand count for other player remain unaffected: FAIL\n");
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
	printf("Number of failures for gaining 2 treasure cards to hand: %d\n", treasureCtFail);
	printf("Number of failures for hand count: %d\n", handCtFail);
	printf("Number of failures for deck count: %d\n", deckCtFail);
	printf("Number of failures for discard count after playing card: %d\n", discardCtFail);
	printf("Number of failures for supply count: %d\n", supplyCtFail);
	
    return 0;

}