/*
// TestDEBUG
// DoubleLinkedList - Insert Card
void DoubleLinkedList::insertCard(const std::string& hand, const int& bid) {
    std::unordered_map<char, int> content;
    Card* newCard = new Card(hand, bid);
    Card* currentCard = this->head;

    for (const auto& letter : hand) ++content[letter];

    this->addType(content, *newCard);
    if (!this->head){
         this->head = newCard;
    } else {

        while (currentCard->type > newCard->type && currentCard->next) {
            std::cout << currentCard->type << " > " << newCard->type << "\n";       
            currentCard = currentCard->next;
            std::cout << currentCard->type << " > " << newCard->type << "\n";       
        }

        std::cout << "\n\n";

        if (currentCard->type <= newCard->type) {
            std::cout << "AAA\n";
            newCard->prev = currentCard->prev;
            currentCard->prev = newCard;
            newCard->next = currentCard;
            !newCard->prev ? this->head = newCard : newCard->prev->next = newCard;
        } else {
            std::cout << "BBB\n";
            newCard->prev = currentCard;
            currentCard->next = newCard;
        }
       
        std::cout << currentCard->hand << " /// " << currentCard->bid << " /// " << currentCard->type << " ///    " << currentCard->prev << " <------> " << currentCard->next;

        std::cout << "\n";

        std::cout << newCard->hand << " /// " << newCard->bid << " /// " <<  newCard->type <<" ///    " << newCard->prev << " <------> " << newCard->next;

        std::cout << "\n\n";
    }
}


newCard->next = currentCard->next;
currentCard->next = newCard;
newCard->prev = currentCard;
!newCard->next ? this->tail = newCard : newCard->next->prev = newCard;


if (!newCard->next && !newCard->prev) {
                newCard->prev = currCard;
                newCard->next = currCard->next;
                currCard->next = newCard;
            }


currCard = firstOfTheType;
checked = false;
while (currCard->type == newCard->type) {
    currIndex = std::distance(strArr.begin(), std::find(strArr.begin(), strArr.end(), currCard->hand[i]));
    newIndex = std::distance(strArr.begin(), std::find(strArr.begin(), strArr.end(), newCard->hand[i]));
    if (currIndex > newIndex) {
        if (!checked) {
            firstOfTheType = lastOfTheType = currCard;
            checked = true;
        }
        else lastOfTheType = currCard;
    }
    if (currCard->next) currCard = currCard->next;
    else break;
}

if (firstOfTheType == lastOfTheType) {
    currCard = firstOfTheType;
    newCard->next = currCard->next;
    currCard->next = newCard;
    newCard->prev = currCard;
    !newCard->next ? this->tail = newCard : newCard->next->prev = newCard;
    return;
}
*/