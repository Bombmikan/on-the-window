#pragma once

//ノードの状態を定義
enum class Status {
	Success,	//成功
	Failure,		//失敗
	Running		//実行中
};

//ノード基底クラスをつくる
class Node {
public:
	virtual ~Node() = default;
	virtual Status update() = 0;	//毎フレーム呼ばれるメイン処理
};

class Selector : public Node {
	Array<std::shared_ptr<Node>> children;
public:
	void addChild(std::shared_ptr<Node> child) { children.push_back(child);
	}

	Status update() override {
		for (auto& child : children) {
			Status s = child->update();
			if (s == Status::Success) return Status::Success;
			if (s == Status::Running) return Status::Running;
		}
		return Status::Failure;
	}
};

class Sequence : public Node {
	Array<std::shared_ptr<Node>> children;
public:
	void addChild(std::shared_ptr<Node> child) { children.push_back(child);
	}

	Status update() override {
		for (auto& child : children) {
			Status s = child->update();
			if (s == Status::Failure) return Status::Failure;
			if (s == Status::Running) return Status::Running;
		}
		return Status::Success;
	}
};
//　体力が低いかチェックする条件ノード(BTD)
class CheckHealth : public Node {
	int threshold;
public:
	CheckHealth(int t) : threshold(t) {}
	Status update() override {
		//本来は外部のデータをみる
		return (10 < threshold) ? Status::Success : Status::Failure;
	}
};

//ログを出すノード
class PrintLog : public Node {
	String message;
public:
	PrintLog(String msg) : message(msg) {}
	Status update()override {
		Print << message;
		return Status::Success;
	}
};

