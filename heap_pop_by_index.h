#pragma once
#include<iterator>
template<typename ITER, typename DIFF, typename PR>
void Pop_heap_by_index(ITER iterBeg, DIFF endOffSet, DIFF hole, PR& pr)
{
#define GET_LEFT_CHILD_INDEX(index) (((index+1)<<1) - 1)
#define GET_RIGHT_CHILD_INDEX(index) ((index+1)<<1)
#define GET_PARENT_INDEX(index)	(((index+1)>>1) - 1)

	if (endOffSet < 2 || hole == endOffSet-1)
		return;

	std::iter_swap(iterBeg + hole, iterBeg + (endOffSet - 1));

	endOffSet -= 1;
	if (hole > 0 && pr(*(GET_PARENT_INDEX(hole) + iterBeg), *(hole + iterBeg))) 
	{
		do
		{
			DIFF parentIndex = GET_PARENT_INDEX(hole);
			std::iter_swap(parentIndex + iterBeg, hole + iterBeg);
			hole = parentIndex;
		} while (hole > 0 && pr(*(GET_PARENT_INDEX(hole) + iterBeg), *(hole + iterBeg)));
	}
	else
	{
		while(endOffSet > GET_LEFT_CHILD_INDEX(hole))
		{
			//std::iterator_traits<ITER>::value_type* p = &*(iterBeg + GET_LEFT_CHILD_INDEX(hole));
			auto leftChildIndex = GET_LEFT_CHILD_INDEX(hole);
			auto rightChildIndex = GET_RIGHT_CHILD_INDEX(hole);
			auto destIndex = leftChildIndex;
			if (rightChildIndex < endOffSet)
			{
				if (pr(*(iterBeg + leftChildIndex), *(iterBeg + rightChildIndex)))
					destIndex = rightChildIndex;
			}
			if (pr(*(iterBeg + hole), *(iterBeg + destIndex)))
			{
				std::iter_swap(iterBeg + hole, iterBeg + destIndex);
				hole = destIndex;
			}
			else break;
		} 
	}
#undef GET_LEFT_CHILD_INDEX
#undef GET_RIGHT_CHILD_INDEX
#undef GET_PARENT_INDEX
}
