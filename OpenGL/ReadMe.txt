<WindRunner>

*Keyboard input
Space Bar 입력을 통해 character을 점프시킬 수 있다.
Shift + Space Bar 입력을 통해 character을 높게 점프시킬 수도 있다.

*File explanation
OpenGL Setting이 되어있다.

Entity.cpp & h : 게임 구현에 필요한 객체들의 상위 class를 구현해놓은 파일이다. 나머지 object들은 이 class를 상속하여 구현한다.
Ground.cpp & h : 게임의 배경이 되는 바닥에 해당하는 class를 구현해 놓은 파일이다. 게임 화면 하단 1/4를 차지하는 흙색 직사각형에, newground객체를 통해 새로운 ground를 동적할당 받을 수 있다.
Character.cpp & h  : Charater 객체에 해당하는 class를 구현해 놓은 파일이다. space 키와 shift 키 입력을 통해 위 방향으로만 점프할 수 있다. Motion Animation을 추가하였다.
Fire.cpp & h : Fire 객체에 해당하는 class를 구현해 놓은 파일이다. 2초 마다 임의의 y좌표에서 생성된다. 캐릭터와 충돌할 경우 게임이 종료된다.
Star.cpp & h : Star 객체에 해당하는 class를 구현해 놓은 파일이다. 1초 마다 임의의 y좌표에서 생성된다. 캐릭터와 충돌할 경우 점수가 5점 증가한다.
Wind_runner.cpp : main함수가 포함된 파일이다.
GameManager.cpp & h : 게임 실행 전반을 담당하는 class를 구현해 놓은 파일이다. 각 객체를 draw,reshape하고 각 객체를 생성하고 충돌 후 삭제하는 대부분의 행위를 담당한다.
Mush.cpp & h : Mush 객체에 해당하는 class를 구현해 놓은 파일이다. ground 위에서 좌,우로 움직이며 캐릭터가 밟을 경우 버섯을 없애고 낮게 점프한다. 캐릭터가 버섯에 부딪힐 경우 게임이 종료된다.