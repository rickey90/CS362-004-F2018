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
   

    printf ("TESTING Smithy Card\n");

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

    //test if we gain 3 cards into our hands after playing smithy
    printf("\nTest case: Hand count after drawing 3 cards\n");
    G.whoseTurn = 0;
    G.hand[0][4] = smithy;
    G.playedCards[0] = copper;
    before = G.handCount[0] - 1;
    cardEffect(smithy, 0, 0, 0, &G, 4, 0);
    printf("Count before = %d,  Count after = %d\n", before, G.handCount[0]);
    compareVal(before + 3, G.handCount[0]);

    //test if the deck count of player has decremented by 3
    printf("\nTest case: Deck count of player after drawing 3 cards\n");
    printf("Count before = 5,  Count after = %d\n", G.deckCount[0]);
    compareVal(2, G.deckCount[0]);


    //test if smithy has been removed from hand after playing it
    printf("\nTest case: Smithy card has been removed from hand\n");
    printf("Card at pos 4 before = 13,  Card at pos 4 after = %d\n", G.hand[0][4]);
    compareVal(4, G.hand[0][4]);

    //test if count of played cards incremented by 1 after adding smithy to it
    printf("\nTest case: Played card count after playing smithy\n");
    printf("Count before = 1,  Count after = %d\n", G.playedCardCount);
    compareVal(2, G.playedCardCount);

    //test if smithy has been added to played cards
    printf("\nTest case: Smithy has been added to played cards pile\n");
    printf("Last card in played pile before smithy = 4,  After = %d\n", G.playedCards[G.playedCardCount]);
    compareVal(smithy, G.playedCards[G.playedCardCount]);

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