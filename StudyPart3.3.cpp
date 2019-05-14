#include "StudyPart3.h"
#include "Vertex.h"

void Part3::useParticle(LPDIRECT3DDEVICE9 device)
{
	// 포인터 스프라이트의 렌더 상태 설정
	device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	device->SetRenderState(D3DRS_POINTSIZE, 3);
	device->SetRenderState(D3DRS_POINTSIZE_MIN, 2);
	device->SetRenderState(D3DRS_POINTSIZE_MAX, 5);

	/*
	D3DRS_POINTSPRITEENABLE - 현재 지정된 텍스처를 포인트 스프라이트의 텍스처 매핑에 이용
	POINTSCALEENABLE - 포인트 크기를 뷰 스페이스 단위로 해석하도록 지정 파티클에 원근 부여
	POINTSIZE - 포인트 스프라이트 크기 지정

	*/

	/*
	파티클은 많은 속성으로 이루어져 있으며, 다양한 속성을 가진 구조체를 통해 관리하면 편할 것이다
	*/


}
