
#ifndef __HEAP_OPERATION_H__
#define __HEAP_OPERATION_H__

#include<functional>

#define GET_LEFT_CHILD_INDEX(index) (((index+1)<<1) - 1)
#define GET_RIGHT_CHILD_INDEX(index) ((index+1)<<1)
#define GET_PARENT_INDEX(index)	(((index+1)>>1) - 1)



template<typename ITER, typename DIFF, typename PR>
void Heap_pop_to_bottom_by_index(ITER iterBeg, DIFF endOffSet, DIFF hole, PR& pr)
{
	if (endOffSet < 2 || hole == endOffSet - 1)
		return;

	typename std::remove_reference<decltype(*iterBeg)>::type holeValue = std::move(*(iterBeg + (endOffSet - 1)));
	*(iterBeg + (endOffSet - 1)) = std::move(*(iterBeg + hole));

	endOffSet -= 1;
	if (hole > 0 && pr(*(GET_PARENT_INDEX(hole) + iterBeg), holeValue))
	{
		do
		{
			DIFF parentIndex = GET_PARENT_INDEX(hole);
			*(iterBeg + hole) = std::move(*(parentIndex + iterBeg));
			hole = parentIndex;
		} while (hole > 0 && pr(*(GET_PARENT_INDEX(hole) + iterBeg), holeValue));
	}
	else
	{
		while (endOffSet > GET_LEFT_CHILD_INDEX(hole))
		{
			auto leftChildIndex = GET_LEFT_CHILD_INDEX(hole);
			auto rightChildIndex = GET_RIGHT_CHILD_INDEX(hole);
			auto destIndex = leftChildIndex;
			if (rightChildIndex < endOffSet)
			{
				if (pr(*(iterBeg + leftChildIndex), *(iterBeg + rightChildIndex)))
					destIndex = rightChildIndex;
			}
			if (pr(holeValue, *(iterBeg + destIndex)))
			{
				*(iterBeg + hole) = std::move(*(iterBeg + destIndex));
				hole = destIndex;
			}
			else break;
		}
	}
	*(iterBeg + hole) = std::move(holeValue);
}

template<typename ITER, typename DIFF, typename PREDICATE, typename CHANGEVALUE_TYPE, typename OPERATION>
void Heap_change_index_value(ITER begIter, DIFF endOffSet, DIFF hole, PREDICATE &pr, const CHANGEVALUE_TYPE &v, OPERATION &op)
{

	typename std::remove_reference<decltype(*begIter)>::type holeValue = op(std::move(*(begIter + hole)), v);
	if (hole > 0 && pr(*(begIter + GET_PARENT_INDEX(hole)), holeValue)) 
	{
		do 
		{
			auto parentIndex = GET_PARENT_INDEX(hole);
			*(begIter + hole) = std::move(*(begIter + parentIndex));
			hole = parentIndex;
		} while (hole > 0 && pr(*(begIter + GET_PARENT_INDEX(hole)), holeValue));
	}
	else
	{
		while (GET_LEFT_CHILD_INDEX(hole) < endOffSet)
		{
			auto left = GET_LEFT_CHILD_INDEX(hole);
			auto right = GET_RIGHT_CHILD_INDEX(hole);
			auto dest = left;
			if (right < endOffSet) 
			{
				if (pr(*(begIter + left), *(begIter + right)))
					dest = right;
			}
			if (pr(holeValue, *(begIter + dest)))
			{
				*(begIter + hole) = std::move(*(begIter + dest));
				hole = dest;
			}
			else break;
		}
	}
	*(begIter + hole) = std::move(holeValue);
}

#endif
