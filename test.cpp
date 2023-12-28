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
*/