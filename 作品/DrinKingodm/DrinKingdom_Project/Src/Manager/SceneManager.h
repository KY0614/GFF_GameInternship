#pragma once

#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

// �O���錾
class Fader;
class SceneBase;
class Camera;

class SceneManager
{
public:
	// �񋓌^
	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		STORY,
		OPENING,
		GAME,
		GAMEOVER
	};

	// �����o�[�֐�
	bool Init(void);		// ����������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��
	bool Release(void);		// �������

	// �V�[���؂�ւ����˗�����֐�
	void ChangeScene(SCENE_ID nextID, bool isToFade);		// �V�[���؂�ւ�

	// �V���O���g����
	// -------------------

	// �C���X�^���X�̐���
	// �O������ÓI�ɃC���X�^���X�𐶐�����
	static void CreateInstance(void);

	// �O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂�
	// �C���X�^���X��Ԃ��֐���p�ӂ���
	// �Q�ƌ^�ɂ��Ă��邪�|�C���^�^�ł��悢
	static SceneManager& GetInstance(void);

private:
	// �����o�[�ϐ�
	// ---------------------
	SCENE_ID sceneID_;			// ���݂̃V�[��ID
	SCENE_ID waitSceneID_;		// ���ɑJ�ڂ���V�[��ID

	// �V�[���J�ڒ����̔��f�p�t���O�itrue:�V�[���J�ڒ��j
	bool isSceneChanging_;

	// �t�F�[�h
	Fader* fader_;				// �t�F�[�h�̃C���X�^���X

	// �V�[��
	SceneBase* scene_;			// �V�[���C���X�^���X�Ǘ�

	// �����o�[�֐�
	// --------------------------
	void DoChangeScene(void);		// �V�[����؂�ւ���
	void Fade(void);				// �t�F�[�h�����{�p�֐�

	// �w�肵���V�[���̉���֐�
	void ReleaseScene(SCENE_ID iSceneID);		// �V�[���̉������

	// �V���O���g����
	// -------------------
	SceneManager(void);		// �R���X�g���N�^
	~SceneManager(void);	// �f�X�g���N�^

	// �R�s�[�R���X�g���N�^�𗘗p�ł��Ȃ�����
	SceneManager(const SceneManager& ins);

	// �C���X�^���X�̔j��
	void Destory(void);

	// �ÓI�ȃC���X�^���X�i�[�̈�
	static SceneManager* instance_;

	// �J����
	Camera* camera_;

};