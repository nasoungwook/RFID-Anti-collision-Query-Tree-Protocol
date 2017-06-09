# RFID-Anti-collision-Query-Tree-Protocol
RFID 충돌방지기법, 질문트리 프로토콜

■ 전역변수 IDENTIFICATION
- 1개의 노드가 응답한 횟수를 0으로 초기화 한다.
  
■ 구현한 클래스 설명
● Reader 클래스는 질의주머니를 만드는 클래스 입니다.
1) 기본생성자를 실행시키고 cycle, IDLE, COLLISION을 0으로 초기화.
2) void creatQuery(int tagNum)
- 태그들에게 보내는 질의를 만드는 함수입니다.
- 태그 ID가 응답한 수가 한번 초과되면 스택을 이용해서
string temp와 “1”,“0”을 쌓습니다.
- top을 temp에 넣습니다.
- 위에 쌓은 “0”을 뺍니다.
- 태그 ID가 1이거나 0이면 top을 temp에 저장시키고 
스택에서 뺍니다.
3) string sendQuery()
- 태그들에게 질의를 보내는 함수
- cycle를 출력하고 string temp를 반환한다.
4) void responsQuery(int tagNum)
- 태그들로부터 오는 응답메세지를 처리하는 함수
- 태그 ID가 응답한 횟수인 tagNum이 1이면 IDENTIFICATION을 1증가
- tagNum이 0이면 IDLE를 1증가
- tagNum이 0과1이 아니라면 COLLISION을 1증가한다.
5) void result()
- 마지막 결과를 출력해주는 함수이다.
● Tag 클래스는 태그 아이디를 담고 있는 변수입니다.
1) 기본생성자
- 파일을 실행시킬 때에는 기본생성자가 실행되어 파일을 읽고 ID와 
ID의 개수를 변수에 저장시킵니다.
2) 변환생성자
- ID의 개수를 입력받고 ID를 만들 함수를 호출하고 ID가 반응한 횟수를 -1
로 초기화한다. -1로 초기화하는 이유는 첫 번째로 Reader::creatQuery를 
호출할 때 조건에 안 들어가게 해야 하기 때문이다. 
3) void receiveQuery(string querybag)
- querybag는 질의를 담고있습니다. 질의가 비어있으면 모두가 응답하고 
2보다 큰 의미없는 숫자 4를 ID의 응답한 횟수에 저장합니다.
- querybag가 비어있지 않으면 querybag를 출력하고 ID랑 비교해서 겹치면
몇 개인지 확인하고 저장합니다.
4) int sendReader()
- ID가 응답한 count를 반환합니다.
5) void tagprint()
- 태그의 정보를 출력하는 함수
6) void creat_bin(int n)
- 태그의 ID를 만들 개수를 입력받아 ID를 만드는 함수
- 십진수로 1~15 중 n개만큼 무작위로 뽑아서 이진수로 변환하여 
문자열에 저장한다.
● Simulator 클래스는 프로젝트를 구현하는 클래스이다.
1) 기본생성자
- num는 1번 파일 실행과 2번 사용자입력을 저장하는 변수로 0으로 
초기화 시킨다.
2) void start()
- 프로그램을 시작하는 함수
- 1번을 num에 저장하면 파일실행을 구현한다.
- 2번을 num에 저장하면 사용자입력을 구현한다.
- 반복해서 IDENTIFICATION이 ID개수 보다 작으면 실행됩니다.
  
■ 구현한 메인한수 설명
- srand((unsigned int)time(NULL));// 시드값을 바꿔준다.
- Simulator를 선언하고 start()를 호출해서 프로그램을 시작한다.

■ 실행화면
![01](http://blogfiles.naver.net/MjAxNzAxMTlfMjg1/MDAxNDg0ODA5MjU4ODg1.Fgn2qyG-X1Gjv4RugYiVrmmbNmYoypPkgmopEWfl1ggg.GREUyi_ll-2dBKKxRWSrZK3x3YRkfyK3SPY4GFAIeSEg.PNG.wsn026/20170119_155944.png)
![02](http://blogfiles.naver.net/MjAxNzAxMTlfMjA5/MDAxNDg0ODA5MjY2MTgy.b5RbmRPzr90CtCmtK7BkHM52PEAm3exFn3zWYr_MnI8g.8st-2g7zAdQX4PwyoX-kTPcfZ4li31NAU9fnhjvfyCEg.PNG.wsn026/20170119_160025.png)
