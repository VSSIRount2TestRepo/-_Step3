

# MQTT 구현

1. mosquitto라는 broker프로그램을 받는다 (다운로드 - https://mosquitto.org/download/)
2. `C:\Program Files\mosquitto`으로 환경변수 경로 설정 뒤, cmd창에서 `mosquitto -v`로 브로커 실행.

![broker.PNG](img%2Fbroker.PNG)

3. Unreal Engine 5에서 MQTT 플러그인을 활용해 blueprint툴을 사용할 수 있게 한다.

4. 제공되는 blueprint functions을 활용해 client와 subscriber를 작성한다
![mqttlogic.PNG](img%2Fmqttlogic.PNG)


5. 브로커와 서로 상호 작동하는지 본다.
![broker connection.PNG](img%2Fbroker%20connection.PNG)
클라이언트가 브로커에 접속했고, 메시지를 교환한 이력이 뜬다.


# MQTT 설명 / Modbus 설명

---

## MQTT란?

Message Queuing Telemetry Transport의 약자이며

MQTT 유틸리티 플러그인은 Message Queuing을 활용해 클라이언트 기능을 Blueprint로 연계해주는 역활을 한다.

또한 MQTT는 request-response방식을 사용하는 Restful 방식이 아닌 publish/subscribe 모델을 기반으로한 TCP 통신 기법을 사용한다.

-  BluePrint란?
비쥬얼 스크립팅 툴로, 논리 관계와 프로세스 단계를 UI로 표현하여 더 쉬운 개발환경을 조성 해주는 툴이다.

   
프로토콜의 종류중 하나이며 스마트 센서, 착용 부품들, IoT기기들은 대채로 제한적인 bandwidth을 통해 데이터를 송/수신을 하기 때문에 필요한 기술이다.
일반적인 MQ와의 차이는 디바이스와 클라우드 사이에서 통신을 주로 이용하기 때문에 IoT환경구축에 이점이 있다.

### 특징

- **확장성** : 적은 코드 수와 적은 파워 사용으로 IoT 디바이스에게 부담을 덜어준다. 때문에 수십만 개의 장비를 늘리는 것이 가능하다.


- **의존성** : 간혹 위성 데이터 통신을 사용하여 데이터를 교환하는 경우가 있는데 low-bandwidth와 빠른 응답속도로 연결이 끊기더라고 빠른 재접속을 통해 원활한 통신을 가능하게 한다.


- **보안** : 메시지 암호화 기능이 내장되어 있고, OAuth, TLS1/3, Certificate와 같은 Authentication 프로토콜을 사용할 수 있다.


- **호환성** : 파이선으로 사용이 가능하고 편리한 기능성 덕분에 빠른 개발 환경을 조성한다.


### MQTT의 원칙

- **Space decoupling**

  Publisher와 Subscriber는 서로 IP정보와 포트번호를 교환하지 않기 때문에 서로의 위치를 모른다. 그러므로 해당 정보를 일일히 보관 할 필요가 없기에 공간이 확보되고 불필요한 검증 단계를 건너뛴다.


- **Time decoupling**

  Publisher와 Subscriber는 서로 동일한 네트워크 연결성을 가질 필요가 없다.

- **Synchronization decoupling**

  Publisher와 Subscriber의 메시지들은 서로 방해가 되지 않는다. 그 이유는 Subscriber가 Publisher의 명령을 지속적으로 기다리는 것(pull-based)이 아닌. Push-based messaging event 이기 때문이다.

### MQTT 구성

- **MQTT Client** :  MQTT 라이브러리가 실행되어 메시지를 다루는 주체를 가르킨다. MQTT를 이용해 네트워크를 통해 송/수신을 하는 모든 디바이스에나 해당된다.


- **MQTT Broker** : 여러 클라이언스 사이에 발생되는 통신에서 메시지 조율을 담당한다. 다음과 같은 역활을 수행한다
  - MQTT 클라이언트 인증과 권한 부여
  - 분석을 위한 다른 디바이스로 메시지 릴레이
  - 손실된 클라이언트 세션과 메시지 관리


- **MQTT Connection** : Client와 브로커가 서로 통신을 시작하는 행위를 일컷는다.
  1. Client는 MQTT브로커로 `CONNECT` 메시지를 전송해 연결 시도
  2. MQTT브로커가 확인을 하고 승인을 할때 클라이언트에 `CONNACK`을 전송
  3. Client와 Broker사이 TCP/IP 통신 연결 체결.


### MQTT 작동 원리

- **MQTT Topic** : Kafka, AMQ Topic과 동일
  

- **MQTT publish** : MQTT 클라이언트는 메시지 패킷에 Topic과 데이터를 byte 포맷으로 변형하여 전송한다. 이때 클라이언트가 수신된 데이타 포맷(Text, XML, JSON, binary)을 결정한다.


- **MQTT subscribe** : MQTT 클라이언트는 브로커에게 SUBSCRIBE 메시지를 보내 특정 토픽과 연결하여 Topic과 관련된 메시지를 수신한다.


### MQTT over WSS

- web socket(full-duplex mode) 기능 허용. TCP 프로토콜을 통해 전이중 통신을 허용해 stateful 기능을 보장. 그러나 추가 데이터가 헤더에 추가되어 송/수신 되어야 하는 데이터가 커지는 단점을 가진다.


### AWS연동

AWS IoT Core을 이용해 수십만개의 기기와 연동해서 MQTT, HTTPS, MQTT over WSS, LoRaWAN 통신 방식을 선택적으로 사용할 수 있다.


---

## Modbus 란?

Modbus는 시리얼 통신을 기반으로 한 자동화 통신 프로토콜이며 Device-to-Device 통신을 가능하게 한다.
Modbus 프로토콜은 쉽게 말해 수신자가 패킷이 자기것이 아니면 무시하는 약속을 말한다.

기기들간의 네트워크 연결 및 통신연결방식 프로토콜 종류는 다음과 같이 있다.
 - Ethernet ip
 - Ether cat
 - Modbus
 - Hart
 - profi bus
 - profi net

이중 Modbus가 흔하게 쓰인다고 한다 (출처 - https://www.youtube.com/watch?v=txi2p5_OjKU).

Modbus는 가장 오래됐으면서도 가장 많이 쓰이는 기법이며 서로 다른 회사에서 출시된 기기들간의 통신 규약도 매우 중요하게 여기는데 Modbus통신 규약을 사용하면 공통된 언어와 규약으로 통신 할 수 있는 이점이 있다. 

Supervisory 기기가 각 기기에서 보내는 데이터 바이트들을 재해석해서 서로 상호작용이 되게 명령을 재변환 한다.
 
Response-request 방식으로 Master가 Slave에게 명령 하달하는 방식. 혹은 Slave가 Master에게 정보를 전달한다.

### Modbus 통신 종류

- Modbus TCP
  - TCP프로토콜을 이용한 이터넷 모드. 호환성이 뛰어남
- Modbus Plus
- Modbus ASCII
  - RTU전송 모드에 비해 시간이 걸림. 그러나 터미널 프로그램 상에서 데이터 추적이 용이해서 사용.
- Modbus RTU
  - bitrate: 9600bps
  - 바이너트 통신, 16진수 문자 사용하여 통신시간 단축.


### 호환되는 물리 시리얼 통신 종류

- RS-232: 1대1 통신만 지원, 외부 환경에 의해 데이터 변형가능성 높음.
- RS-422: 전이중 통신 지원하기 때문에 동시 송수신 가능. 그러나 늘어난 통신선으로 비용 발생이 올라감.
- RS-485: 장거리, 속도, bandwidth 크기에서 우위를 선보임 - 두개의 송/수신 전용 선이 있음. 멀티드롭 방식으로 여러대의 단말기들을 한개의 통신회선에 연결가능. 주소 판단 장치와 버퍼 기억 장치가 있어야함.
- TCP/IP Ethernet - 패킷단위로 데이터를 전송 다른 통신 방식과 규약을 포함 할 수 있음

### Modbus 메시지 구조

- Peer-to-peer
- Point-to-point
- Multi-point


### Open protocol
- 특정 모델을 정하고 해당 프로콜에 속한 디바이스들은 통신이 가능하게끔 한다
  - Request/Reply
  - Master/Slave
  - Client/Slaver
  - Tranport Layer Security


