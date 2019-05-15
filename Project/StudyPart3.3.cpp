#include "StudyPart3.h"
#include "Vertex.h"

void Part3::useParticle(LPDIRECT3DDEVICE9 device)
{
	// ������ ��������Ʈ�� ���� ���� ����
	device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	device->SetRenderState(D3DRS_POINTSIZE, 3);
	device->SetRenderState(D3DRS_POINTSIZE_MIN, 2);
	device->SetRenderState(D3DRS_POINTSIZE_MAX, 5);

	/*
	D3DRS_POINTSPRITEENABLE - ���� ������ �ؽ�ó�� ����Ʈ ��������Ʈ�� �ؽ�ó ���ο� �̿�
	POINTSCALEENABLE - ����Ʈ ũ�⸦ �� �����̽� ������ �ؼ��ϵ��� ���� ��ƼŬ�� ���� �ο�
	POINTSIZE - ����Ʈ ��������Ʈ ũ�� ����

	*/

	/*
	��ƼŬ�� ���� �Ӽ����� �̷���� ������, �پ��� �Ӽ��� ���� ����ü�� ���� �����ϸ� ���� ���̴�
	*/


}
