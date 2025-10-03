# Project 04 단계별 체크리스트

## 단계 1: 양방향 연결 리스트 클래스 구현
- [x] Linked_List_Node, Linked_List_Iterator, Linked_List 각 클래스를 작성하고 friend 관계 및 private 멤버를 정의한다.
- [x] 노드에 데이터와 prev/next 포인터, 생성자/소멸자를 구현하고 복사/대입을 private으로 막는다.
- [x] Linked_List에 기본/복사 생성자, 대입 연산자, 소멸자, add_at_front/back, remove_all_items 등 요구된 멤버를 구현하고 항목 수를 추적한다.
- [x] Linked_List_Iterator에 advance/at_end/remove_at_iterator/insert_before_iterator/access/reset/invalidate 등 공개 멤버를 구현한다.
- [x] int/char 등 기본 타입으로 동작하는 버전과 테스트 프로그램(find_del, display_list 등)으로 기능을 검증한다.
- [x] 검증 후 template 버전으로 일반화해 다양한 데이터 타입에서 재사용 가능하게 만든다.

- **버그 메모:** `Peasant::display_status()`가 존재하지 않는 `location`/`destination` 멤버에 직접 접근해 링킹 실패가 발생했고, `Person`의 캡슐화된 접근자(`get_location`, `get_destination`)를 사용하도록 수정해 리스트 마이그레이션 이후에도 정상 컴파일됩니다.
- **버그 메모:** Warrior/Soldier/Archer가 `Person`의 제거된 멤버들(`id_num`, `location`, `world_ptr`, `health` 등)에 직접 접근해 컴파일이 실패했으며, `baseData`와 접근자들을 사용하도록 수정하고 월드 포인터 유효성 검사를 추가해 문제를 해소했다.
## 단계 2: Person 객체에 이름과 소멸자 추가
- [ ] Person 클래스에 동적 char 배열(name) 멤버를 추가하고 최대 128자 이름을 입력 받아 저장한다.
- [ ] new 명령 처리 시 사용자에게 이름을 받아 저장하고 필요한 임시 버퍼를 관리한다.
- [ ] display_status/restore/save 등 관련 멤버 함수에 이름 출력과 저장 로직을 반영한다.
- [ ] Person 및 파생 클래스의 소멸자에서 "Soldier Jack is deallocated" 형식 메시지를 출력한다.
- [ ] Person의 복사 생성자와 대입 연산자를 private으로 선언해 이름 버퍼가 잘못 복사되지 않도록 제한한다.

## 단계 3: 연결 리스트로 Game_World 수정
- [ ] Game_World의 Person 포인터 배열을 Linked_List<Person *> 기반 구조로 교체하고 관련 멤버를 갱신한다.
- [ ] update_all_object()와 generate_display() 등 main에서 호출할 새 public 멤버 함수를 정의한다.
- [ ] get_object_ptr()를 리스트 순회 방식으로 다시 구현하고 존재하지 않을 때 0을 반환한다.
- [ ] get_new_ID() 함수를 추가해 새로운 객체에 사용 가능한 ID를 배정한다.
- [ ] 'd' 명령을 추가해 모든 객체의 display_status()를 호출하고 이름이 알파벳 순으로 출력되도록 한다.
- [ ] update 중 dead 상태 객체를 리스트에서 제거하고 메모리를 반환하며 필요 시 is_attacking을 false로 리셋한다.
- [ ] start_scan()/get_next_scan_ptr()를 추가해 스캔 전용 iterator 상태를 캡슐화하고 Archer 검색 로직을 지원한다.
- [ ] save()에서 Linked_List 복사 생성자와 대입 연산자를 호출해 동작을 검증하고 소멸자 메시지가 기대대로 출력되는지 확인한다.

## 단계 4: 예외 처리 도입
- [ ] 문자열 메시지를 보관하는 bad_input 예외 클래스를 정의한다.
- [ ] 입력 검증 구간마다 잘못된 경우 "throw bad_input("Error ...")" 형태로 예외를 발생시킨다.
- [ ] main에서 catch 절을 추가해 오류 메시지를 출력하고 버퍼를 flush한 뒤 다음 명령을 대기한다.

## 단계 5: Observer 클래스 추가
- [ ] Person을 상속하는 Observer 클래스를 정의하고 이동 목적지 목록을 Linked_List<Real_Pair>로 저장한다.
- [ ] move 명령으로 여러 목적지를 입력받아 목록에 추가하고 순차적으로 이동하도록 구현한다.
- [ ] 이동 중 반경 10 이내 객체를 탐지해 "I see P1("Joe") at location (10,5)" 형식으로 보고한다.
- [ ] Observer 생성 명령('O')을 추가하고 동적으로 생성된 객체를 Linked_List에 등록한다.
- [ ] Observer 소멸 시 Linked_List에서 제거되고 메모리가 해제되도록 보장한다.
- [ ] Observer의 복사 생성자와 대입 연산자를 private으로 만들어 객체 복사를 금지한다.
