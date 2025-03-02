#include <iostream>
#include "LinkedList.h"

int main() {
    // 연결 리스트 생성
    Linked_List<int> list;

    // 리스트에 값 추가
    list.add_at_front(10);
    list.add_at_front(20);
    list.add_at_back(30);
    list.add_at_back(40);

    // 이터레이터를 사용하여 리스트 순회
    std::cout << "Linked List Elements: ";
    Linked_List_Iterator<int> iter(list);
    while (!iter.at_end()) {
        std::cout << iter.access_at_iterator() << " ";
        iter.advance();
    }
    std::cout << std::endl;

    // 특정 위치에 삽입
    iter.reset_from_list(list);
    iter.advance(); // 두 번째 위치로 이동
    iter.insert_before_iterator(25);

    // 삽입 후 다시 출력
    std::cout << "After Insert: ";
    Linked_List_Iterator<int> iter2(list);
    while (!iter2.at_end()) {
        std::cout << iter2.access_at_iterator() << " ";
        iter2.advance();
    }
    std::cout << std::endl;

    // 특정 위치에서 노드 삭제
    iter.reset_from_list(list);
    iter.advance(); // 두 번째 위치로 이동
    iter.remove_at_iterator();

    // 삭제 후 다시 출력
    std::cout << "After Remove: ";
    Linked_List_Iterator<int> iter3(list);
    while (!iter3.at_end()) {
        std::cout << iter3.access_at_iterator() << " ";
        iter3.advance();
    }
    std::cout << std::endl;

    return 0;
}
