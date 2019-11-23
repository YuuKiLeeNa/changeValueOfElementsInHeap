#ifndef __HEAP_OPERATION_H__
#define __HEAP_OPERATION_H__
#include<functional>


template<typename ITER, typename DIFF, typename PR>
void Pop_heap_to_bottom_by_index(ITER iterBeg, DIFF endOffSet, DIFF hole, PR& pr)
{
#define GET_LEFT_CHILD_INDEX(index) (((index+1)<<1) - 1)
#define GET_RIGHT_CHILD_INDEX(index) ((index+1)<<1)
#define GET_PARENT_INDEX(index)	(((index+1)>>1) - 1)

	if (endOffSet < 2 || hole == endOffSet - 1)
		return;

	typename std::remove_reference<decltype(*iterBeg)>::type holeValue = std::move(*(iterBeg+(endOffSet-1)));
	*(iterBeg + (endOffSet - 1)) = std::move(*(iterBeg +hole));

	endOffSet -= 1;
	if (hole > 0 && pr(*(GET_PARENT_INDEX(hole) + iterBeg), std::ref(holeValue)))
	{
		do
		{
			DIFF parentIndex = GET_PARENT_INDEX(hole);
			*(iterBeg + hole) = std::move(*(parentIndex + iterBeg));
			hole = parentIndex;
		} while (hole > 0 && pr(*(GET_PARENT_INDEX(hole) + iterBeg), std::ref(holeValue)));
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
			if (pr(std::ref(holeValue), *(iterBeg + destIndex)))
			{
				*(iterBeg + hole) = *(iterBeg + destIndex);
				hole = destIndex;
			}
			else break;
		}
	}
	*(iterBeg + hole) = std::move(holeValue);
#undef GET_LEFT_CHILD_INDEX
#undef GET_RIGHT_CHILD_INDEX
#undef GET_PARENT_INDEX
}

#endif
