#ifndef QUEUE_LINKLIST
#define QUEUE_LINKLIST
template <class T>
class Queue {
private:
	struct Node {
		T data;
		Node *next;
	};
private:
	Node *head;
	Node *rear;
	int  queueSize;
public:
	Queue() :head(), rear(), queueSize(0) { };
	~Queue() {
		while (!empty())
			pop();
	}
	void push(const T &val) {
		Node *new_node = new Node;
		new_node->data = val;
		new_node->next = NULL;
		if (head == NULL && rear == NULL) {
			head = rear = new_node;
		}
		else {
			rear->next = new_node;
			rear = new_node;
		}
		++queueSize;
	}
	T pop() {
		if (!empty()) {
			T i;
			Node *temp = head;
			i =temp->data;
			head = head->next;
			delete temp;
			--queueSize;
			return i;
		}
	}

	T front() const {
		if (!empty())
			return head->data;
	}

	T back() const {
		if (!empty())
			return rear->data;
	}

	bool empty() const {
		return queueSize == 0;
	}

	int size() const {
		return queueSize;
	}
	T del(const T &val) {    //从head往后数，删除第几个，总共size个
		if (!empty()&& val<=queueSize)
		{
			Node *temp = head;
			Node *temp2 = head;
			if (1 == val) { pop(); return 0; }
			if (queueSize == val) {
				for (int i = 1; i < val - 1; i++) {
					temp = temp->next;
				}
				rear = temp;
				temp = rear->next;
				rear->next = NULL;
				delete temp;
				--queueSize;
				return 0;
			}
			for (int i=1; i <  val-1; i++) {
				temp = temp->next;
				temp2 =temp->next;
			}
			temp->next = temp2->next;
			delete temp2;
			--queueSize;
		}
		else {
			return 1;
		}
	}

	T Query(const T &val) {//查询队列中的第val个元素
		if (!empty())
		{
			Node *temp = head;
			for (int e=1; e < val; e++) {
				temp = temp->next;
			}
			return temp->data;
		}
		else {
			return 1;
		}
	}
};
#endif