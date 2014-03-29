OpenCV1
=======
1) Error diffusion dithering
  - 수업에서 다루었던 오차확산 디더링을 C/C++을 이용하여 구현한다. 
  - 영상을 입력하고 픽셀에 대한 연산을 처리하기위해서 OpenCV를 사용하거나 또는 다른 영상처리 library를 사용할 수 있다. 그러나 오차확산디더링 알고리즘은 직접 구현하여야 한다. 
  - 입력영상은 lena.jpg를 사용하고 흑백(grey level)영상으로 변환한 후 디더링 알고리즘을 적용하고 결과도 흑백영상으로 저장한다. 
  - 컬러영상의 경우 RGB로 분리한 후 각각의 컬러채널에 대하여 디더링을 구현하고 이들을 다시 합성하여 새로운 컬러 영상을 생성한다. 
  - Visual C++ project 파일과 흑백 및 컬러 2장의 영상을 제출한다.

2) Gaussian filtering 
  - Blur 필터의 하나인 Gaussian 필터링을 적용한다. 
  - 필터의 크기는 5x5로 정하고 σ=2로 정한다. 
  - 우선 5x5 크기의 Gaussian 필터를 구한다. 2차원 Gaussian 공식을 이용하고 5x5 필터값을 모두 더하면 1.0이 되도록 정규화한다. 
  - Gaussian 필터를 영상에 correlation 하고 새로운 영상을 생성한다. 이때 새로운 영상의 가장자리 2pixel은 계산하지 않는다. 예를들어 correlation은 (2,2)에서 시작하여 계산한다. 
  - 입력영상은 lena.jpg을 사용하고 흑백과 컬러에 대하여 모두 결과를 만든다. 
  - Visual C++ project 파일과 Blur 된 2장의 결과영상을 제출한다. 
