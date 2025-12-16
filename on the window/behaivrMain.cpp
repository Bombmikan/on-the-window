#include "beheaivrTree.h"
# include <Siv3D.hpp> // Siv3D v0.6.16 (描画や入力、時間管理のために利用します)

using namespace std;
void Main() {
	//ツリーの構築
	auto root = make_shared<Selector>();

	auto seq = make_shared<Sequence>();
	seq->addChild(make_shared<CheckHealth>(20));
	seq->addChild(make_shared<PrintLog>(U"Health is low!"));

	root->addChild(seq);
	root->addChild(make_shared<PrintLog>(U"Normal state"));

	while (System::Update()) {
		//マイフレーム
		root->update();
	}
	
}
