# &#128271; Netwhat 시험을 통과해보자.
<br>

### 결과는 모든 문제를 다 맞아야 100점임.

<br>

## &#128270; 준비물

<br>

1. ipv4 ipv6는 몇 비트를 쓰는지 등에 대한 기~본적인 개념 정도만 머리 속에 넣어둔다.
2. netwhat 전용 계산기를 만든 minckim 님의 프로그램을 켠다.

- minckim 님의 프로그램 켜는 방법 : 
  - 레포 안에 있는 `netwhat_calculator.c` 를 실행한다. (`gcc netwhat_calculator.c`)
  - 생성된 `.out` 파일을 실행한다.

3. 다음 velog 창을 띄워 놓는다. (daelee님의 블로그 !) 

   : [https://velog.io/@hidaehyunlee/Netwhat-%EC%97%B0%EC%8A%B5%EB%AC%B8%EC%A0%9C-%EC%A0%95%EB%A6%AC](https://velog.io/@hidaehyunlee/Netwhat-연습문제-정리)

4. google에다가 private address 검색한 결과창 띄워놓기.

<br><br>

## 시험 시작. &#128270;

<br>제한 시간은 10분이다. 

띄워둔 창들의 도움을 받으면 10분은 넉넉하게 느껴질 것이다. (본인은 7분 걸림)

시험은 netwhat 프로젝트 등록 후 ` netwhat.42.fr` 에 접속하여 시작한다.

<br>

시험은 크게 두 파트로 나뉜다.

1. 주소를 구하는 문제(체감상 3 / 4를 차지하는 문제)

2. 개념을 묻는 문제.

<br>

여기에 대해 1번은 우리가 실행시킨 `.out` 파일을 이용해 모두 풀 수 있고,

2번은 띄워둔 velog와 google로 해결가능하다.

<br>

### PART 1

주소를 구하는 문제도 여러 가지 유형이 있는데, 크게 3 가지가 있다. 

<br><br>

먼저 네트워크 및 브로드캐스트 주소를 구하는 문제이다. 

`What is the network address of` 로 시작하며 전체 문제는 

`What is the network address of a host with an IP address of 182.161.121.118/24?` 

이런 식이다. <br>

여기서 `182.161.121.118/24` 이것만 긁어서 우리가 실행시켜둔 `.out`  에 붙여넣고 엔터를 치면

<br>

![image-20200701025740894](https://k.kakaocdn.net/dn/X5mHT/btqFg4B3bmN/8l7f1UCAxUN67bgGBsVjGK/img.png)

<br>

위와 같은 화면이 뜬다. 

`What is the network address of `으로 시작하는 이런 유형의 문제의 경우 위 결과에서 

`network_id` 부분을 정답으로 체크하고 넘어가면 된다. 

<br><br>

다음으로 호스트 주소 수를 구하는 문제다. 

<br>

` What is the maximum number of IP addresses that can be assigned to hosts`  

로 시작하며 전체 예제 문장은 이렇다. 

`What is the maximum number of IP addresses that can be assigned to hosts on a local subnet using the 255.255.255.128 subnet mask?`  

<br>

혹은 `how many hosts` 가 문장 중간에 들어간 경우도 같은 유형이다. 

<br>

이 경우에는 복사 붙여넣기를 두 번 해야 한다. 이 유형의 경우만 그렇다. 

실행시킨 .out 파일에서  

`type option`  에 `255.255.255.128:255.255.255.128`를 복사해 붙여넣는다. 

(cmd + v : cmd + v와 같다.)

<br>

그러면 아래와 같은 결과가 나오는데, 

<br>

![image-20200701030622884](https://k.kakaocdn.net/dn/TSnub/btqFeErxvSh/x62IrxAkwcxJlSYDuUysCK/img.png)

<br>위에서 num_of_host가 정답이 된다.

<br><br>

세 번째 유형은 호스트 주소의 '범위'를 구하는 유형이다.

<br>

키워드는 `valid host range`이 문장 중간에 나오는 것이다. 

주로 다음과 같이 출제된다.

`Which of the following proposals is the valid host range for the subnet on which the IP address 1.93.149.6/17 resides?`

이 경우 `1.93.149.6/17` 이 부분을 복사해 .out 프로그램에 붙여 넣으면

![image-20200701031018181](https://k.kakaocdn.net/dn/oEDCD/btqFgxxVQLk/GFCwReUhRhjVPYwCYBxyPK/img.png)

위와 같은 화면이 뜬다.  

위 화면에서 `host_range`라고 되어 있는 곳이 실제 범위가 된다. 

<br>

- 참고로 `Which of the following IP addresses is a private address?` 와 같이 생긴 문제가 나온다면 google에다가 private address를 치면 나오는 그 범위 안에 있는 보기를 정답으로 체크하고 넘기면 된다.

* 혹은 우리가 실행시켜놓은 프로그램에서 p를 입력하고 엔터를 친 뒤

<br>

![image-20200701031451104](https://k.kakaocdn.net/dn/r0PVz/btqFhkScvOb/nSnzJv3nZ1VSvUwNuOfz61/img.png)

<br>위와 같이 생긴 보기 전체를 긁어 붙여넣으면 

<br>

![image-20200701031554443](https://k.kakaocdn.net/dn/b5t4Yq/btqFftW9psM/9rPPHPdxv5ICho8IzPaFU0/img.png)

<br>위와 같이 뜬다. 당연히 정답은 yes가 적힌 부분. 

(개인적으로 이거 구현한거 보고 굉장히 놀랐다.) 

<br>

빠져나오는 건 q를 입력하고 엔터.

<br><br><br>

### PART 2

나머지 부분에 대해서는 개념들 (특히 UDP/TCP)에 관한 문제다. 

그런데 netwhat 문제들이 몇 해 째 바뀌질 않아서 단순히 문제 일부를(혹은 전체를) 긁어서 구글에다가 치기만 해도 정답이 나온다. 

개념들에 대해 모르는 것이 있을 때에는 문제의 키워드가 된다 싶은 부분을 복사해서 

띄워놓은 velog에서 `cmd + f` 로 찾아보고 결과가 없으면 google에다가 그대로 긁어 검색하자. 

내 경우 커버되지 않은 문제는 없었다. 

<br><br>

## &#128270; 시험 끝!

여기까지 따라왔다면 시험을 무난히 치렀을 것이다. 

결과창에 뜨는 코드를 복사하고, `answer.txt`  라는 이름의 파일을 만들어 그 안에 붙여넣는다. 

그리고 그 파일을 git repo에 넣고 해당 파일 제출하면 끝!

요약 : 툴을 개발한 `minckim`님은 진짜 ... &#128077;

다음 사이트에서도 확인 
https://42kchoi.tistory.com/155
