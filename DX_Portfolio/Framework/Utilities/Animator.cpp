#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT farmeCount, Vector2 startPos, Vector2 endPos, bool bReversed)
	:clipName(clipName), frameCount(frameCount), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();
	
	// 이에니멩;션이 그려져 있는 텍스처의 길이
	Vector2 clipSize = endPos - startPos;

	// 특수경우에는 에셋 또는 코드를 수정해야 함
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// 텍셀 프레임 -> UV상의 좌표를 알아낼수 있음
	texelFrameSize.y = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyFrame;

	for (UINT i = 0; i < frameCount; i++) {
		keyFrame.x = texelStartPos.x + (texelFrameSize.x * i);
		keyFrame.y = texelStartPos.y;

		keyFarmes.push_back(keyFrame);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	// 애님 클립스를 모를수도 있기 떄문에
	// 이게 어짜피 다 지워도 동적할당된 친구만 딜리트 하기 때문에, 두번째 있는 세컨드만 지움
	for (auto clip : animClips) SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	// 에니메이션 경과 시간이 플레이 레이트보다 커질경우 
	// 에니메이션 진행
	if (deltaTime >= playRate) {

		// 역재생이 아니라면
		if (currentClip->bReversed == false) {
			currentFrameIndex++; // 프레임 인덱스 증가 (그릴 그림을 다음그림으로 변경)

			// 프레임도 0index, 둘이 같아지면 0으로 초기화
			// 이과정을 통해 내가 알고 있는 원통형의 그것이 되는거임
			if (currentFrameIndex == currentClip->frameCount) currentFrameIndex = 0;

			// 현재 실행할 그림을 위에서 지정한 번호의 그림으로 설정
			// 처음에 0부터 시작을 하기 때문에 0부터 안줘도 됨
			currentFrame = currentClip->keyFarmes[currentFrameIndex];
		}

		// 역재생 -> 이라도 짤라 넣는 순서는 역재생이 아닐때랑 동일하기 때문에 상관 ㄴㄴ
		else {
			currentFrameIndex--;

			// 베열의 최대치
			if (currentFrameIndex == -1) currentFrameIndex = currentClip->frameCount - 1;

			currentFrame = currentClip->keyFarmes[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}

	// 프레임 바뀔꺼 아니면 증가나 하셈 ㅇㅇ
	else deltaTime += Time::Delta();
}

// 애니메이터에게 클립 자체를 넘겨주는 함수
// 애니메이터가 사용할 클립을 넣는 과정
void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	/*
	// 실행중인 클립은 없고, 애니메이션이 있을경우
	if (currentClip == nullptr && CheckExist(clipName) == true)
		currentClip = animClips.find(clipName)->second;
	// 멥은 파인드 명령어와 키를 통해서 찾을수 있는데, 이걸 클립 네임으로 찾아서 
	// 쿼런트 클립에 지금 실행될(호출해야될) 클립만 넣어주는거임
	// 여기부분의 역할은 아래 조건문 검사식 부분에서 'currentClip->clipName == clipName'에서 터질수 있기 떄문이다.
	// 따라서 이부분이 있어야 한다.
	였지만... 터지면 살릴꺼임 --> 아래의 조건문을 수정하면서 살릴 이유가 없어짐
	*/
	
	
	
	// 실행중인 클립이 있지만 실행할 클립과 같은 경우/*else*/
	if (currentClip != nullptr) 
		if(currentClip->clipName == clipName) return;

	// 클립이 존제 한다면
	// 실행중인 에니메이션과 새로 실해할 애니메이션이 다를 경우 교체 하기 위해
	if (CheckExist(clipName)) {
		currentClip = animClips.find(clipName)->second;

		// 실행중인 에니매이션이 있을때 그 델타타임을 초기화 시키고 새로운 에니매이션이 델타 타임을 사용 시키기 때몬이다.
		deltaTime = 0.0f;

		if (currentClip->bReversed == true) 
			currentFrameIndex = currentClip->frameCount - 1;
		

		else currentFrameIndex = 0;
		
		currentFrame = currentClip->keyFarmes[currentFrameIndex];
	}
}
