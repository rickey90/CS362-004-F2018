#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int fail_count = 0;


void compareVal(int a, int b)
{
	if( a == b)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		fail_count++;
	}
}

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int before;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
   

    printf ("TESTING Adventurer Card\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    for(int i = 0; i < G.deckCount[0]; i++) //make all cards in deck copper
    {
        G.deck[0][i] = copper;
    }

    for(int i = 0; i < G.handCount[0]; i++) //make all cards in hand copper
    {
        G.hand[0][i] = copper;
    }

    //test if we gain 2 additional cards after playing adventurer
    printf("\nTest case: Hand count after gaining 2 treasure cards.\n");
    G.whoseTurn = 0;
    G.hand[0][4] = adventurer; //add an adventurer card to hand
    G.deck[0][4] = smithy;  //ensure we have just 3 treaure cards in deck
    G.deck[0][3] = smithy;
    G.playedCards[0] = copper;
    before = G.handCount[0] - 1;
    cardEffect(adventurer, 0, 0, 0, &G, 4, 0);
    printf("Count before = %d,  Count after = %d\n", before, G.handCount[0]);
    compareVal(before + 2, G.handCount[0]);

    //test if last two cards are in fact treaaure cards
    printf("\nTest case: Gained cards are treasure cards\n");
    if(G.hand[0][G.handCount[0]-1] == copper && G.hand[0][G.handCount[0]-2] == copper)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
        fail_count++;
    }

    //test if deck count went down by atleast 2 cards
    printf("\nTest case: Deck count went down by atleast 2\n");
    printf("Count before = 5,  Count after = %d\n", G.deckCount[0]);
    if(G.deckCount[0] <= 3)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
        fail_count++;
    }

    //test if discard count went up by atleast 2 cards
    printf("\nTest case: Discard count went up by atleast 2\n");
    printf("Count before = 0,  Count after = %d\n", G.discardCount[0]);
    if(G.discardCount[0] >= 2)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
        fail_count++;
    }

    //test if count of played card went up by 1
    printf("\nTest case: Played cards count went up by one\n");
    printf("Count before = 0,  Count after = %d\n", G.playedCardCount);
    compareVal(1, G.playedCardCount);

    //test if the supply count for the kingdom cards and victory are not changed 
    printf("\nTest case: Supply of kingdom and victory cards have not changed\n");
    for(int i = 0; i < 10; i++)
    {
        if(k[i] == great_hall || k[i] == gardens) //set before for kingdom or victory card
        {
            before = 8;
        }
        else
        {
            before = 10;
        }

        printf("Supply count for %d card before = %d, after = %d - ", i, before, G.supplyCount[k[i]]);
        compareVal(before, G.supplyCount[k[i]]);
    }

    //test if the other players state is unchanged
    printf("\nTest case: Other players state remain the same as before playing card\n");
    for(int i = 0; i < numPlayer; i++)
    {
        if(i != 0)
        {
            printf("Hand count of player %d before = 0, after = %d - ", i, G.handCount[i]);
            compareVal(0, G.handCount[i]);
            printf("Deck count of plater %d before = 10, after = %d - ", i, G.deckCount[i]);
            compareVal(10, G.deckCount[i]);
        }
    }


    if(!fail_count)
    {
        printf("\nALL TEST CASES PASSED!\n");
    }
    else
    {
        printf("\nFAILED TEST CASES: %d\n", fail_count);
    }


    return 0;
}