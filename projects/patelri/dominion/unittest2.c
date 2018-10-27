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
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
   

    printf ("TESTING gainCard()\n");

    //testing gain card if the supply of the card is empty
    printf("\nTest case: Gain card when supply is empty\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.whoseTurn = 0;
    G.supplyCount[adventurer] = 0;
    r = gainCard(adventurer, &G, 0, 0);
    printf("return = %d,  expected = -1\n", r);
    compareVal(-1, r);

    //test that gain card is added to the discard pile
    printf("\nTest case: Count of discard after gained card is added to discard pile\n");
    G.supplyCount[smithy] = 10;
    r = gainCard(smithy, &G, 0, 0);
    printf("count = %d,  expected = 1\n", G.discardCount[0]);
    compareVal(1, G.discardCount[0]);

    //test that gained card is in discard pile
    printf("\nTest case: Card is added to discard pile\n");
    printf("card = %d,  expected = 13\n", G.discard[0][G.discardCount[0]-1]);
    compareVal(13, G.discard[0][G.discardCount[0]-1]);

    //test that gained card is added to the deck
    printf("\nTest case: Count of deck after gained card is added to deck pile\n");
    G.supplyCount[adventurer] = 10;
    r = gainCard(adventurer, &G, 1, 0);
    printf("count = %d,  expected = 6\n", G.deckCount[0]);
    compareVal(6, G.deckCount[0]);

    //test that gained card is in the deck pile
    printf("\nTest case: Card is added to deck pile\n");
    printf("card = %d,  expected = 7\n", G.deck[0][G.deckCount[0]-1]);
    compareVal(7, G.deck[0][G.deckCount[0]-1]);

    //test that gained card is added to the player's hand
    printf("\nTest case: Count of hand after gained card is added to the hand\n");
    r = gainCard(adventurer, &G, 2, 0);
    printf("count = %d,  expected = 6\n", G.handCount[0]);
    compareVal(6, G.handCount[0]);

    //test that gained card is in the hand
    printf("\nTest case: Card is added to hand\n");
    printf("card = %d,  expected = 7\n", G.hand[0][G.handCount[0]-1]);
    compareVal(7, G.deck[0][G.handCount[0]-1]);

    //test that gained card decrements the supply
    printf("\nTest case: Supply count after gaining card\n");
    G.supplyCount[adventurer] = 5;
    r = gainCard(adventurer, &G, 0, 0);
    printf("count = %d,  expected = 4\n", G.supplyCount[adventurer]);
    compareVal(4, G.supplyCount[adventurer]);


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