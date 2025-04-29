/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <new>

struct ListNode
{
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution
{
	/*
	 * [2]-[4]-[3] + [5]-[6]-[4] = [7]-[0]-[8]
	 * 왼쪽부터 순회하면서 더하여 값 생성.
	 * 생성된 값으로 노드 생성.
	 * 생성된 노드 리스트에 추가.
	 * 더한 값이 두자릿수가 나오면 자릿수를 쪼개어 값 생성. 올린 값(10의 자리)는 다음 덧셈 때 같이 더함.
	 * 105 + 15 = 120. [5]-[0]-[1] + [5]-[1] -> 5 + 5 = 10. 10 % 10 = 0, 10 / 10 = 1. [0]. 1 + 0 + 1 = 2. [0]-[2]. 1. [0]-[2]-[1].
	 */
	private:
		int		_addNumbers(int first_sum, int round_up, int* next_round_up)
		{
			int	sum = first_sum + round_up;
			*next_round_up = sum / 10;
			return sum % 10;
		}
		
		void	_addNextNumbers(ListNode* add_to_next, ListNode* l1, ListNode* l2, int round_up)
		{
			if (!l1 && !l2 && !round_up) return;

			int	v1 = 0;
			int v2 = 0;
			ListNode*	n1 = NULL;
			ListNode*	n2 = NULL;
			if (l1)
			{
				v1 = l1->val;
				n1 = l1->next;
			}
			if (l2)
			{
				v2 = l2->val;
				n2 = l2->next;
			}

			int	next_round_up;
			int	sum = _addNumbers(v1 + v2, round_up, &next_round_up);
			sum %= 10;

			ListNode*	new_node = new ListNode(sum);
			add_to_next->next = new_node;

			_addNextNumbers(new_node, n1, n2, next_round_up);
		}
	public:
		ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
		{
			int	first_round_up;
			int	first_sum = _addNumbers(l1->val + l2->val, 0, &first_round_up);
			ListNode*	sum = NULL;
			try
			{
				sum = new ListNode(first_sum);
				_addNextNumbers(sum, l1->next, l2->next, first_round_up);
			}
			catch (const std::bad_alloc& e)
			{
				ListNode*	next;
				while (sum)
				{
					next = sum->next;
					delete sum;
					sum = next;
				}
				return NULL;
			}
			return sum;
		}
};
