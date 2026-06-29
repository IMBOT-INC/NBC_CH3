# NBC_CH3

Unreal Engine 5.7 기반 C++ 게임플레이/UI 연습 프로젝트입니다. 현재 CH5 파트에는 메인 메뉴, 스테이지 이동, 플레이어 HUD, 스태미나/웨이브/시간 표시, 체크포인트, DeadLine 기반 게임오버, C++ 기반 UMG 위젯 구조가 포함되어 있습니다.

## 개발 환경

- Unreal Engine: 5.7
- 메인 모듈: `NBC_CH3`
- 사용 중인 UI 관련 모듈/플러그인:
  - `UMG`
  - `ModelViewViewModel`
  - `FieldNotification`

## 현재 게임 흐름

```text
CH5 메뉴 맵
  -> WBP_MainMenu 표시
  -> StartGame()
  -> GameInstance.LevelMaps[0]에 등록된 첫 번째 스테이지로 이동

게임플레이 스테이지
  -> HUD에서 스태미나, 레벨, 웨이브, 남은 시간 표시
  -> CheckPoint 도달 시 웨이브/레벨 진행
  -> DeadLine과 충돌 시 플레이어 제거 후 GameOver 위젯 표시

GameOver
  -> 현재 레벨 재시작
  -> 게임 종료
```

## 주요 시스템

### 레벨 진행

`UCH5_GameInstance`가 레벨 진행 상태를 관리합니다.

관련 파일:

```text
Source/NBC_CH3/Public/CH5/CH5_GameInstance.h
Source/NBC_CH3/Private/CH5/CH5_GameInstance.cpp
```

역할:

- `StartGame()` : `LevelMaps[0]`에 등록된 첫 번째 스테이지를 엽니다.
- `RestartCurrentLevel()` : 현재 `CurrentLevelIndex`의 레벨을 다시 엽니다.
- `OpenLevelByIndex()` : 인덱스에 해당하는 Soft Object 맵을 엽니다.
- `OpenNextLevel()` : 다음 스테이지로 이동합니다.
- `OpenMainMenu()` : `CH5` 메인 메뉴 맵으로 이동합니다.
- `QuitGame()` : 게임을 종료합니다.

`LevelMaps` 배열은 GameInstance 블루프린트 또는 기본값에서 설정해야 합니다.

### 게임플레이 GameMode

`ACH5_MyGameMode`는 게임플레이 맵의 UI 상태와 게임오버 처리를 담당합니다.

관련 파일:

```text
Source/NBC_CH3/Public/CH5/CH5_MyGameMode.h
Source/NBC_CH3/Private/CH5/CH5_MyGameMode.cpp
```

역할:

- 스테이지 시작 시 입력 모드를 Game Only로 복구합니다.
- 게임 중 마우스 커서를 숨깁니다.
- `ShowGameOverWidget()`을 통해 GameOver 위젯을 표시합니다.
- 게임오버 시 게임을 일시정지하고 UI 입력 모드로 전환합니다.

게임플레이 맵에서는 `ACH5_MyGameMode`를 상속한 BP GameMode를 사용하는 것이 좋습니다. 그래야 에디터에서 `GameOverWidgetClass`에 `WBP_GameOver`를 지정할 수 있습니다.

### 시작/메뉴 GameMode

`ACH5_StartMode`는 메뉴 맵 전용 GameMode입니다.

관련 파일:

```text
Source/NBC_CH3/Public/CH5/CH5_StartMode.h
Source/NBC_CH3/Private/CH5/CH5_StartMode.cpp
```

역할:

- 메인 메뉴 위젯 생성
- Viewport에 메뉴 추가
- 입력 모드를 UI Only로 변경
- 마우스 커서 표시

이 GameMode는 메뉴 맵에서만 사용하고, 실제 게임플레이 맵에서는 사용하지 않습니다.

## UI 구조

### 메인 메뉴

C++ 위젯 클래스:

```text
Source/NBC_CH3/Public/CH5/UI/MainMenuWidget.h
Source/NBC_CH3/Private/CH5/UI/MainMenuWidget.cpp
```

WBP 설정:

```text
WBP_MainMenu
  Parent Class: MainMenuWidget
  필요한 버튼 이름:
    StartButton
    QuitButton
```

버튼 동작:

- `StartButton` -> `UCH5_GameInstance::StartGame()` 호출
- `QuitButton` -> `UCH5_GameInstance::QuitGame()` 호출

주의: `BindWidget`을 사용하므로 WBP 안의 버튼 이름이 C++ 변수명과 정확히 같아야 합니다.

### 게임오버 메뉴

C++ 위젯 클래스:

```text
Source/NBC_CH3/Public/CH5/UI/GameOverWidget.h
Source/NBC_CH3/Private/CH5/UI/GameOverWidget.cpp
```

WBP 설정:

```text
WBP_GameOver
  Parent Class: GameOverWidget
  필요한 버튼 이름:
    RestartButton
    QuitButton
```

버튼 동작:

- `RestartButton` -> `UCH5_GameInstance::RestartCurrentLevel()` 호출
- `QuitButton` -> `UCH5_GameInstance::QuitGame()` 호출

### 플레이어 HUD

C++ 위젯 클래스:

```text
Source/NBC_CH3/Public/CH5/UI/PlayerHUDWidget.h
Source/NBC_CH3/Private/CH5/UI/PlayerHUDWidget.cpp
```

ViewModel:

```text
Source/NBC_CH3/Public/CH5/UI/ViewModels/CH5_MVVMViewModel.h
Source/NBC_CH3/Private/CH5/UI/ViewModels/CH5_MVVMViewModel.cpp
```

HUD는 MVVM 스타일의 데이터 흐름을 사용합니다.

```text
Pawn / GameState 원본 데이터
  -> Delegate 또는 Timer 갱신
  -> PlayerHUDWidget
  -> CH5_PlayerHUDViewModel setter 호출
  -> FieldNotify 발생
  -> WBP 바인딩 갱신
```

권장 바인딩:

```text
TextBlock.Text        <- StaminaText
ProgressBar.Percent  <- GetStaminaPercent
TextBlock.Text        <- LevelText
TextBlock.Text        <- WaveText
TextBlock.Text        <- TimeText
```

중요: `ProgressBar.Percent`는 `0.0 ~ 1.0` 값을 요구합니다. 따라서 원본 스태미나 값을 직접 연결하지 말고 `GetStaminaPercent`에 바인딩해야 합니다.

## 게임플레이 액터

### 플레이어

기본 플레이어 구현:

```text
Source/NBC_CH3/Public/CH4/PawnCharacter.h
Source/NBC_CH3/Private/CH4/PawnCharacter.cpp
```

CH5용 플레이어 래퍼:

```text
Source/NBC_CH3/Public/CH5/CH5_PawnCharacter.h
Source/NBC_CH3/Private/CH5/CH5_PawnCharacter.cpp
```

현재 역할:

- 이동 입력 처리
- 시점 회전 처리
- 달리기 입력 처리
- 스태미나 감소/회복
- 스태미나 변경 Delegate Broadcast
- `HUDWidgetClass`를 통한 HUD 위젯 생성

### GameState

```text
Source/NBC_CH3/Public/CH5/CH5_GameState.h
Source/NBC_CH3/Private/CH5/CH5_GameState.cpp
```

역할:

- 현재 웨이브 상태 관리
- 제한 시간 관리
- 웨이브 변경 Delegate Broadcast
- 다음 웨이브/다음 레벨 진행

### CheckPoint

```text
Source/NBC_CH3/Public/CH5/CheckPoint.h
Source/NBC_CH3/Private/CH5/CheckPoint.cpp
```

역할:

- 플레이어가 체크포인트에 도달하면 `ACH5_GameState::CheckPoint()`를 통해 웨이브 진행

### DeadLine

```text
Source/NBC_CH3/Public/CH5/DeadLine.h
Source/NBC_CH3/Private/CH5/DeadLine.cpp
```

역할:

- 플레이어와의 Overlap 감지
- Blueprint 이벤트 `OnDestroy(Location)` 호출
- 플레이어 액터 제거
- `ACH5_MyGameMode::ShowGameOverWidget()` 호출

## 에디터 설정

### GameInstance 설정

Project Settings:

```text
Maps & Modes
  Game Instance Class = BP_CH5_GameInstance 또는 CH5_GameInstance 기반 Blueprint
```

설정 예시:

```text
LevelMaps[0] = 첫 번째 게임플레이 스테이지
LevelMaps[1] = 두 번째 게임플레이 스테이지
LevelMaps[2] = 세 번째 게임플레이 스테이지
```

### 메뉴 맵 설정

`CH5` 메뉴 맵:

```text
World Settings
  GameMode Override = BP_CH5_StartMode 또는 CH5_StartMode 기반 Blueprint
```

설정:

```text
MainMenuWidgetClass = WBP_MainMenu
```

### 게임플레이 맵 설정

`CH5-1`, `CH5-2`, `CH5-3` 같은 게임플레이 맵:

```text
World Settings
  GameMode Override = BP_CH5_MyGameMode 또는 CH5_MyGameMode 기반 Blueprint
```

설정:

```text
GameOverWidgetClass = WBP_GameOver
```

## 빌드 참고

Unreal C++ 빌드 중 아래와 같은 PCH/pagefile 메모리 오류가 발생할 수 있습니다.

```text
C3859: failed to create virtual memory for PCH
The paging file is too small for this operation to complete
```

이 경우 Windows page file을 늘리거나 병렬 빌드 수를 줄여 빌드합니다.

개발 중 메모리 부족 상황에서 성공했던 빌드 명령:

```powershell
& 'D:\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat' NBC_CH3Editor Win64 Development -Project='D:\Unreal Projects\NBC_CH3\NBC_CH3.uproject' -WaitMutex -NoXGE -MaxParallelActions=1
```

## 개발 메모

- UI 배치와 디자인은 WBP에서 처리합니다.
- 버튼 클릭 기능과 레벨 이동 로직은 C++ Widget / GameInstance에서 처리합니다.
- `NativeConstruct()`에서 버튼 Delegate를 바인딩합니다.
- `NativeDestruct()`에서 Delegate를 해제해 중복 바인딩을 방지합니다.
- 레벨 흐름과 게임오버 규칙은 GameMode / GameInstance에 둡니다.
