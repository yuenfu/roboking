## 1. 업데이트 파일 구성

[로보킹 업데이트](https://www.lgservice.co.kr/mobile/simple/selectSimpleSearchDetail.do?itemId=1434517084839&gubun=SCS&type=keyword)의 경우에는 아래의 3개 파일을 이용하여 업데이트를 하게 된다.
( 모바일을 통해 업데이트 명령을 전송 하게 되고 로보킹이 충전중일때 가능 한 것으로 보아 충전기를 통해 파일을 받는것 같다.)

### 1-1. Update.sh

> ".dat , .axf 파일 확인 후에 업데이트를 하기 위해서 파일을 실행한다."

__SOURCE_PATH__가 '/mnt/usb' 인 것을 보아 업데이트는 USB를 통해 업데이트가 진행 되는 것을 알 수 있다.

### 1-2. Update.dat

> "업데이트와 관련된 파일들이 Packing되어 있어 .axf파일을 통해 unpacking 작업을 해주어야 한다."

.dat 파일은 패킹되어 있어 어느정도 __데이터를 구조화__ 시켜 저장하게 된다. ( 바이너리 패킹 ㅇㅇ )
구조화 되어 있는 데이터로는 .axf파일과 비교하며 분석한 결과 아래와 같이 나타낼 수 있다.

#### 1-2-1. 메인 헤더 ( stMainHeader )

> "메인 헤더에는 펌웨어에 대한 정보가 담겨있으며 0x1c크기의 구조체를 가지게 된다."

|name|offset|size|description|
|:---:|:---:|:---:|:---:|
|unRevision|0|4|펌웨어 확인과 관련되어 있는것 같다.(언패킹시에는 사용 x)|
|unFirmwareSize|4|4|펌웨어의 크기 ( 메인헤더 제외 )|
|unChecksum|8|4|펌웨어의 체크섬|
|szPartNumber|0xc|0x10|vision board part number ( default : "ALL" )|


#### 1-2-2. 서브 헤더 ( stReadSubHeader )

> "unpacking될 파일들의 추가적인 정보가 담겨져 있으며 0x8 크기를 가지게 된다."

|name|offset|size|description|
|:---:|:---:|:---:|:---:|
|unDataSize|0|4|파일크기|
|unPathLength|4|2|파일이름 길이|
|unFlag|6|2|?|

### 1-3. Update.axf

> "update.dat 파일을 언패킹하고 펌웨어 업데이트 작업을 수행하는 바이너리"

~~~

## Reference

[firmware](https://www.dropbox.com/s/a86on4yo90py0s1/FullBackupFW16552.zip?dl=0)

