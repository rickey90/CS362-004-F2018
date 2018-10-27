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
    int numPlayer = 4;
    int before;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
   

    printf ("TESTING Council Room Card\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.whoseTurn = 0;
    G.numBuys = 0;
    G.playedCardCount = 0;

    //test if player gained 4 additional cards to hand
    printf("\nTest case: Hand count after playing card(+4).\n");
    G.hand[0][4] = council_room; //add a village card to hand
    before = G.handCount[0] - 1;
    cardEffect(council_room, 0, 0, 0, &G, 4, 0);
    printf("Count before = %d,  Count after = %d\n", before, G.handCount[0]);
    compareVal(before + 4, G.handCount[0]);

    //test if number of buys went up by one
    printf("\nTest case: Number of buys added\n");
    printf("Count before = 0,  Count after = %d\n", G.numBuys);
    compareVal(1, G.numBuys);

    //test if all other players hand increased by one
    printf("\nTest case: Hand and Deck count of all players\n");
    for(int i = 1; i < numPlayer; i++)
    {
        printf("Player %d: Hand count before = 0, after = %d - ", i, G.handCount[i]);
        compareVal(1, G.handCount[i]);
        printf("Deck count of player %d before = 10, after = %d - ", i, G.deckCount[i]);
            compareVal(9, G.deckCount[i]);
    }


    //test if council card has been removed from the hand
    printf("\nTest case: Council room card removed from hand\n");
    printf("Card as pos 4 before = 8, Card as pos 4 after = %d\n", G.hand[0][4]);
    if(G.hand[0][4] != council_room)
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
            before = 12;
        }
        else
        {
            before = 10;
        }

        printf("Supply count for %d card before = %d, after = %d - ", i, before, G.supplyCount[k[i]]);
        compareVal(before, G.supplyCount[k[i]]);
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