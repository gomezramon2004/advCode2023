/*
// TestDEBUG
void checkTypeHand(std::string hand) {
    std::vector<std::pair<char, int>> content;
    for (int i = 0; i < hand.size(); ++i) {
        auto itFound = std::find_if(content.begin(), content.end(), [hand_i = hand[i]](const auto& pair) {
            return pair.first == hand_i;
        });
        if (itFound != content.end()) {
            ++itFound->second;
        } else {
            content.emplace_back(hand[i], 1);
        }
    }

    for (const auto& element : content) {
        std::cout << element.first << " / " << element.second << "\n";
    }
    std::cout << "\n";


    if (content.size() == 1 ) {
        std::cout << "Five of a kind.\n";
        return;
    }

    if (content.size() == 2 ) {
        if (content[0].second == 4 || content[0].second == 1) {
            std::cout << "Four of a kind.\n";
            return;
        }
        std::cout << "Full House.\n";
        return;
    }

    if (content.size() == 3 ) {
        for (const auto& element : content) {
            if (element.second == 2) {
                std::cout << "Two pair.\n";
                return;
            } else if (element.second == 3) {
                std::cout << "Three of a kind.\n";
                return;
            }
        }
        std::cout << "Full House.\n";
        return;
    }

    if (content.size() == 4 ) {
        std::cout << "One pair.\n";
        return;
    }

    if (content.size() == 5 ) {
        std::cout << "High Card.\n";
        return;
    }
    
}


void DoubleLinkedList::insertCard(const std::string& hand, const int& bid) {
    Card* newCard = new Card;
    newCard->hand = hand;
    newCard->bid = bid;

    if (!tail) {
        this->tail = newCard;
    } else {
        tail->next = newCard;
        newCard->prev = tail;
        this->tail = newCard;
    }
}
*/