# UnrealProjectileTest

## Project description
특정 입력을받아 특정 입력에 맞는 발사체를 생성하고, 각 발사체들의 생성 횟수를 화면에 보여준다.
    - Projectile
     1. Character Class 는 입력을 받아 네 가지의 특정 상황이 발생하면 <br>
         그 상황에 맞는 Enum을 Projectile SpawnComponenet에 발사체를 생성하라고 전달.
     2. Projectile SpawnComponent는 받은 Enum 값에 맞는 발사체<br>
         (발사체는 총 네가지로 하나의 Base에서 상속받아 각각 자신에 맞는 기능을 구현)를 생성  
    - Widget
     1. Widget은 WidgetComponent에서 관리.<br>
     2. 게임 시작시 Projectile 생성 횟수를 보여주는 Widget생성<br>
     3. 충전 입력이 들어오면 충전 위젯을 ViewPort에 추가 입력이 끝나면 ViewPort에서 제거<br>
     3. Rest 버튼은 현재 Projectile 생성 횟수를 초기화<br> 

## Development Environment
- VisualStudio 2017
- UnrealEngine 4.25 Release
- Window 10
