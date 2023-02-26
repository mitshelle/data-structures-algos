/*
 *Name: Michelle McGowan, 2001813382, CS 302-1003, Assignment 5
 *Description: play virtual poker & output hand
 *Input: 5 cards w/ face & suit
 *Output: hand ranking + the final hand
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

class cardCompare
{
public:
    // cardssorted(card1, card2)
    bool operator()(const std::string &c1, const std::string &c2)
    {
        if (c1 == c2)
        {
            return false;
        }

        // if c2 is an ace
        if (c2 == "A")
        {
            return true;
        }

        // if c2 is king and c1 is not ace
        if (c2 == "K" && c1 != "A")
        {
            return true;
        }

        // if c2 is QWEEN and c1 not ace or king
        if (c2 == "Q" && (c1 != "A" && c1 != "K"))
        {
            return true;
        }

        // if c2 is jack and c1 not ace king or QWEEN
        if (c2 == "J" && (c1 != "A" && c1 != "K" && c1 != "Q"))
        {
            return true;
        }

        // if c2 is a 10 & c1 is not a, k, QWEEN, or j
        if ((c2[0] == '1' && c2[1] == '0') && (c1 != "A" && c1 != "K" && c1 != "Q" && c1 != "J"))
        {
            return true;
        }

        // if c2 is 1-9 & c1 is 1-9
        if ((c1[0] <= 58 && c1[0] >= 50) && (c2[0] <= 58 && c2[0] >= 50))
        {
            // check if c2 bigger
            if (c2[0] > c1[0])
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    std::unordered_map<std::string, int> faces;
    std::unordered_map<std::string, int> suits;
    std::map<std::string, int, cardCompare> cardsSorted;
    std::vector<std::string> currentHand;
    std::string card;
    int count = 0, input = 0;
    std::string str, newCard, f, s;
    bool isTrue = false;
    bool notSameSuits = false;
    bool royalFL = false;
    std::vector<std::string> sortedRank = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    std::cout << "Welcome to video poker" << std::endl
              << std::endl;

    // propmt for input
    std::cout << "Time to randomly generate hand" << std::endl;
    std::cout << "Ahem ... please enter the 5 cards" << std::endl;

    for (int i = 0; i < 5; i++)
    {
        // get input
        std::cin >> card;
        // save into vector
        currentHand.push_back(card);
    }

    // output
    std::cout << "Current Hand"
              << "\n";
    for (int i = 0; i < 5; i++)
    {
        // output
        std::cout << "[" << i << "]: ";
        std::cout << currentHand[i] << std::endl;
    }

    for (int i = 0; i < 5; i++)
    {
        // check if there is a 10
        if (currentHand[i].length() == 3)
        {
            // then will get the first 2 chars
            // as the face and last char as the suit
            str = currentHand[i].substr(0, 2);
            faces[str] += 1;
            str = currentHand[i].substr(2, 1);
            suits[str] += 1;
        }
        else
        {
            // first char is face & last char is suit
            str = currentHand[i].substr(0, 1);
            faces[str] += 1;
            str = currentHand[i].substr(1, 1);
            suits[str] += 1;
        }

        str = "";
    }

    std::cout << std::endl;
    std::cout << std::endl;

    // put face cards into cardssorted
    for (auto face = faces.begin(); face != faces.end(); face++)
    {
        cardsSorted[face->first] = face->second;
    }

    // loop to get input
    while (true)
    {
        // if 5 then cannot replace cards anymore so break
        if (count == 5)
        {
            break;
        }

        // prompt
        std::cout << "Enter the index of cards you do not want" << std::endl;
        std::cout << "Enter -1 to stop: ";
        std::cin >> input;
        std::cout << std::endl;

        // if -1 then leave & stop
        if (input == -1)
        {
            break;
        }

        // set
        str = currentHand[input];

        // get new card
        std::cout << std::endl;
        std::cout << "Enter new card: ";
        std::cin >> newCard;

        std::cout << "\n";

        // remove from current hand vec
        currentHand.erase(currentHand.begin() + input);

        // check for char lenght
        if (str.length() == 3)
        {
            f = str.substr(0, 2);
            s = str.substr(2, 1);
        }
        else
        {
            f = str.substr(0, 1);
            s = str.substr(1, 1);
        }

        // find the card w/ key want to remove
        auto face = faces.find(f);
        if (faces.find(f) != faces.end())
        {
            // remove from faces & cardssorted map if 1
            if (face->second > 1)
            {
                face->second--;
                cardsSorted.find(f)->second--;
            }
            else
            {
                // if greater then just dec it
                faces.erase(f);
                cardsSorted.erase(f);
            }
        }

        // find the card w/ key want to remove
        auto suit = suits.find(s);
        if (suits.find(s) != suits.end())
        {
            // remove from suits map if 1
            if (suit->second > 1)
            {
                suits.erase(s);
            }
            else
            {
                // if not then just dec it s
                suit->second--;
            }
        }

        // add to current hand vec
        currentHand.insert(currentHand.begin() + input, newCard);
        // add new card to faces & suits & sorted cards
        if (newCard.length() == 3)
        {
            // if a 10 get the first 2 chars
            str = newCard.substr(0, 2);
            // add to faces & sorted
            faces[str] += 1;
            cardsSorted[str] += 1;
            // add suit w/ last char
            str = newCard.substr(2, 1);
            suits[str] += 1;
        }
        else
        {
            // get the first char
            str = newCard.substr(0, 1);
            // add to faces & sorted
            faces[str] += 1;
            cardsSorted[str] += 1;
            // add suit w/ last char
            str = newCard.substr(1, 1);
            suits[str] += 1;
        }

        str = "";
        input = 0;
        count++;
    }

    // output current hand
    std::cout << "Final Hand"
              << "\n";
    for (int i = 0; i < 5; i++)
    {
        std::cout << currentHand[i] << " ";
    }
    std::cout << std::endl;

    // set
    auto fc = faces.begin();
    auto st = suits.begin();

    // loop though cards
    for (auto card = cardsSorted.begin(); card != cardsSorted.end(); card++)
    {
        isTrue = false;
        if (card->second == 3)
        {
            // check for fullhouse
            for (auto fullHous = cardsSorted.begin()++; fullHous != cardsSorted.end(); fullHous++)
            {
                // if card w/ same face is 3 and other card w/ same face is pair
                if (card->second == 3 && fullHous->second == 2)
                {
                    // output
                    std::cout << "Full house: " << card->first << " over "
                              << fullHous->first << "\n";
                    isTrue = true;
                    break;
                }
                else
                {
                    // if not then will be 3 of kind
                    isTrue = false;
                    break;
                }
            }

            if (!isTrue) // 3!!!
            {
                std::cout << "Three of a kind: " << card->first << "\n";
                break;
            }

            if (isTrue)
                break; // just break
        }
        else if (card->second == 4) // if 4 with same face
        {
            std::cout << "4 of a kind: " << card->first << std::endl;
            break;
        }
        else if (cardsSorted.size() == 5)
        {
            int i = 0;
            int j = 13;
            auto straight = cardsSorted.end();
            straight--;
            // loop through to see what rank first sorted card is
            for (i = 0; i < sortedRank.size(); i++)
            {
                if (straight->first == sortedRank[i])
                {
                    break;
                }
            }

            straight = cardsSorted.end();
            straight--;
            str = straight->first;
            // then check if is in ordered
            for (; straight != cardsSorted.begin(); straight--)
            {
                // check if it is the in right order going from highest
                if (straight->first == sortedRank[i])
                {
                    isTrue = true;
                }
                else
                {
                    // if not then NOT straight or straight flush
                    isTrue = false;
                    break;
                }

                i--;
            }

            auto rf = cardsSorted.end();
            rf--;
            // check if it a royal flush
            for (; rf != cardsSorted.begin(); rf--)
            {
                // must be A,K,Q,J,10 so start at 13
                if (rf->first == sortedRank[j])
                {
                    royalFL = true;
                }
                else
                {
                    royalFL = false;
                    break;
                }

                j--;
            }

            // if is straight & all the same suit
            if (isTrue && st->second == 5 && !royalFL)
            {
                auto stfl = cardsSorted.end();
                stfl--;
                std::cout << stfl->first << " high straight flush\n";
                break;
            }
            else if (isTrue && !royalFL) // is straight but not same suit
            {
                auto st = cardsSorted.begin();
                std::cout << "Straight: " << st->first << " to " << str << "\n";
                break;
            }
            else if (!isTrue && st->second == 5 && !royalFL) // is not in ordered but all same suit
            {
                auto fl = cardsSorted.end();
                fl--;
                std::cout << "Flush: " << fl->first << " high\n";
                break;
            }
            else if (royalFL)
            {
                std::cout << "ROYAL FLUSH!!!!!!!!!!!!!\n";
                break;
            }
            else // none of these so high
            {
                auto fl = cardsSorted.end();
                fl--;
                std::cout << fl->first << " high\n";
                break;
            }
        }
        else if (card->second == 2) // if pair
        {
            auto check = card;
            // check if there are two pairs
            for (auto twoPair = check++; twoPair != cardsSorted.end(); twoPair++)
            {
                if (check->second == 2 && twoPair->second == 2)
                {
                    std::cout << "Two pair: " << check->first << " "
                              << twoPair->first << "\n";
                    isTrue = true;
                    break;
                }
                else
                {
                    isTrue = false;
                }
            }

            // just 1 pair
            if (!isTrue && check++->second != 3)
            {
                check--;
                check--;
                std::cout << "Pair: " << check->first << "\n";
                break;
            }

            if (isTrue)
                break;
        }
    }
}
