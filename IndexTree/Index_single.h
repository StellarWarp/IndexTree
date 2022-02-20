#ifndef INDEX_SINGLE_H
#define INDEX_SINGLE_H
#include"Struct.h"
#include"Support.h"
template<class DT>//关键字的类型
class Index
{
	//参数
	static const int M = 10;
	static const int min_key = (M % 2) ? M / 2 + 1 : M / 2;//m/2向上取整
	static const int max_key = M - 1;
	static const int min_i = min_key - 1;
	static const int max_i = max_key - 1;
	int H = 0;

	//结构
	union Pointer;
	struct LayerData
	{
		DT key[max_key];
		unsigned long DataPointer[max_key];
		struct LayerData* next = NULL;
		int num = 0;
	};
	struct LayerN
	{
		DT key[max_key];
		unsigned long DataPointer[max_key];//用于辨识
		Pointer NodePointer[M];
		int num = 0;
	};
	Stack<LayerN*> Path;
	Stack<int> Pathi;
	union Pointer
	{
		LayerData* Dp;
		LayerN* Np = NULL;

		Pointer()
		{
			;
		}
		Pointer(LayerData* P)
		{
			Dp = P;
		}
		Pointer(LayerN* P)
		{
			Np = P;
		}
	};
	Pointer* Master;

	//LayerData的操作函数
	//未完成
	void Find(LayerData& Node, DT value, Line<unsigned long>& DataAddress)
	{
		for (int i = 0; i < max_key;)
		{
			if (value < Node.key[i])
			{
				i++;
			}
			else if (value == Node.key[i])
			{
				DataAddress.IN(Node.DataPointer[i]);
				//同值查找
				i++;
				if (i < Node.num && value == Node.key[i])
				{
					while (i < Node.num && value == Node.key[i])
					{
						DataAddress.IN(Node.DataPointer[i]);
						i++;
					}
					if (i == Node.num)
					{
						Find(*(Node.next), value, DataAddress);
					}
				}
				else if (i == Node.num)
				{
					Find(*(Node.next), value, DataAddress);
				}
				break;
			}
			else
			{
				break;
			}
		}
	}
	bool isfull(LayerData& Node)
	{
		if (Node.num == max_key) return 1;
		else return 0;
	}
	bool islow(LayerData& Node)
	{
		if (Node.num < min_key) return 1;
		else return 0;
	}
	bool ismore(LayerData& Node)
	{
		if (Node.num > min_key) return 1;
		else return 0;
	}
	bool Insert(LayerData& Node, unsigned long DP, DT value)
	{
		int in = DilitarySearch_down(Node.key, 0, Node.num - 1, value);
		InsertArray(Node.key, in, max_i, value);
		InsertArray(Node.DataPointer, in, max_i, DP);
		Node.num++;
		if (in == Node.num - 1) return 1;
		else return 0;

	}
	Pointer Divide(LayerData& Node, unsigned long DP, DT value)
	{
		LayerData* NewNode = new LayerData;
		int in = DilitarySearch_down(Node.key, 0, max_i, value);
		Node.num = M / 2;
		NewNode->num = min_key;
		if (in < min_i)
		{
			MoveArray(Node.key, min_i, max_i, NewNode->key);//将原节点多出的移动到新的节点
			MoveArray(Node.DataPointer, min_i, max_i, NewNode->DataPointer);
			InsertArray(Node.key, in, min_i, value);
			InsertArray(Node.DataPointer, in, min_i, DP);
		}
		else
		{
			MoveArray(Node.key, min_key, max_i, NewNode->key);
			MoveArray(Node.DataPointer, min_key, max_i, NewNode->DataPointer);
			InsertArray(NewNode->key, in - min_i, min_i, value);
			InsertArray(NewNode->DataPointer, in - min_i, min_i, DP);
		}
		NewNode->next = Node.next;
		Node.next = NewNode;
		return Pointer(NewNode);
	}
	int Delete(LayerData& Node, DT value)
	{
		Node.num--;
		int del = DilitarySearch_p(Node.key, 0, Node.num, value);
		DeleteArray(Node.key, del, Node.num, (DT)-1);
		DeleteArray(Node.DataPointer, del, Node.num, (unsigned long)-1);
		return del;
	}
	void Shift(LayerData& Node1, int a1, int b1, LayerData& Node2, int a2)
	{
		MoveArray(Node1.key, a1, b1, Node2.key, a2);
		MoveArray(Node1.DataPointer, a1, b1, Node2.DataPointer, a2);
		int num = b1 - a1 + 1;
		Node1.num -= num;
		Node2.num += num;
	}

	//LayerN的操作函数
	//未完成
	Pointer Find(LayerN& Node, DT value)
	{
		if (value > Node.key[max_key - 1]) return Node.NodePointer[max_key];
		return Node.NodePointer[DilitarySearch_down(Node.key, 0, Node.num - 1, value)];
	}
	bool isfull(LayerN& Node)
	{
		if (Node.num == max_key) return 1;
		else return 0;
	}
	bool islow(LayerN& Node)
	{
		if (Node.num < min_key) return 1;
		else return 0;
	}
	bool ismore(LayerN& Node)
	{
		if (Node.num > min_key) return 1;
		else return 0;
	}

	LayerN* newLayer(Pointer P1, DT value1, unsigned long DP1, Pointer P2, DT value2, unsigned long DP2)
	{
		LayerN* NewNode = new LayerN;
		NewNode->key[0] = value1;
		NewNode->key[1] = value2;
		NewNode->NodePointer[0] = P1;
		NewNode->NodePointer[1] = P2;
		NewNode->DataPointer[0] = DP1;
		NewNode->DataPointer[1] = DP2;
		NewNode->num = 2;
		return NewNode;
	}
	//返回是否最大值
	bool Insert(LayerN& Node, Pointer P, DT value, unsigned long DP)
	{
		int in = DilitarySearch_down(Node.key, 0, Node.num - 1, value);
		InsertArray(Node.key, in, max_i, value);
		InsertArray(Node.NodePointer, in, max_i, P);
		InsertArray(Node.DataPointer, in, max_i, DP);
		Node.num++;
		if (in == Node.num - 1) return 1;
		else return 0;
	}
	bool update(LayerN* Node, int i, DT value, unsigned long DP)
	{
		if (i == Node->num - 1)
		{
			Node->key[i] = value;
			Node->DataPointer[i] = DP;
			if (Path.Nempty())
			{
				update(Path.OUT(), Pathi.OUT(), value, DP);
			}
			return 1;
		}
		else
		{
			Node->DataPointer[i] = DP;
			Node->key[i] = value;
			return 0;
		}
	}
	//不回溯
	void update0(LayerN* Node, int i, DT value, unsigned long DP)
	{
		Node->key[i] = value;
		Node->DataPointer[i] = DP;
	}
	//未完成//查找
	Pointer Divide(LayerN& Node, Pointer P, DT value, unsigned long DP)
	{
		LayerN* NewNode = new LayerN;
		int in = DilitarySearch_down(Node.key, 0, max_i, value);
		Node.num = M / 2;
		NewNode->num = min_key;
		if (in < min_i)
		{
			MoveArray(Node.key, min_i, max_i, NewNode->key);//将原节点多出的移动到新的节点
			MoveArray(Node.NodePointer, min_i, max_i, NewNode->NodePointer);
			MoveArray(Node.DataPointer, min_i, max_i, NewNode->DataPointer);
			InsertArray(Node.key, in, min_i, value);
			InsertArray(Node.NodePointer, in, min_i, P);
			InsertArray(Node.DataPointer, in, min_i, DP);
		}
		else
		{
			MoveArray(Node.key, min_key, max_i, NewNode->key);
			MoveArray(Node.NodePointer, min_key, max_i, NewNode->NodePointer);
			MoveArray(Node.DataPointer, min_key, max_i, NewNode->DataPointer);
			InsertArray(NewNode->key, in - min_i, min_i, value);
			InsertArray(NewNode->NodePointer, in - min_i, min_i, P);
			InsertArray(NewNode->DataPointer, in - min_i, min_i, DP);
		}
		return Pointer(NewNode);
	}
	//未完成//查找
	int Delete(LayerN& Node, DT value, unsigned long DP)
	{
		Node.num--;
		int del = DilitarySearch_p(Node.key, 0, Node.num, value);
		DeleteArray(Node.key, del, Node.num, (DT)-1);
		Pointer Empty;
		DeleteArray(Node.NodePointer, del, Node.num, Empty);
		DeleteArray(Node.DataPointer, del, Node.num, (unsigned long)-1);
		return del;
	}
	//将1移到2
	void Shift(LayerN& Node1, int a1, int b1, LayerN& Node2, int a2)
	{
		MoveArray(Node1.key, a1, b1, Node2.key, a2);
		MoveArray(Node1.NodePointer, a1, b1, Node2.NodePointer, a2);
		MoveArray(Node1.DataPointer, a1, b1, Node2.DataPointer, a2);
		int num = b1 - a1 + 1;
		Node1.num -= num;
		Node2.num += num;
	}

	//函数
	//未完成
	LayerData* FIndLayerData(DT key)
	{
		while (Path.Nempty())
		{
			Path.OUT();
			Pathi.OUT();
		}
		Pointer p = *Master;
		int h = H;
		while (h > 1)
		{
			DT maxkey = Master->Np->key[Master->Np->num - 1];
			if (key > maxkey)
			{
				key = maxkey;
			}
			Path.IN(p.Np);
			int i = DilitarySearch_down(p.Np->key, 0, p.Np->num - 1, key);
			p = p.Np->NodePointer[i];
			Pathi.IN(i);
			h--;
		}
		return p.Dp;

	};
	void LayerNAdd(Pointer P, DT key, unsigned long DP)
	{
		LayerN& CLayer = *Path.OUT();
		Pathi.OUT();
		if (isfull(CLayer))
		{
			Pointer NLayer = Divide(CLayer, P, key, DP);
			if (Master->Np == &CLayer)
			{
				Pointer C(&CLayer);
				delete Master;
				Master = new Pointer(newLayer(C, CLayer.key[min_i], CLayer.DataPointer[min_i],
					NLayer, NLayer.Np->key[min_i], NLayer.Np->DataPointer[min_i]));
				H++;
			}
			else
			{
				update0(Path.Read0(), Pathi.Read0(), CLayer.key[min_i], CLayer.DataPointer[min_i]);
				LayerNAdd(NLayer, NLayer.Np->key[min_i], NLayer.Np->DataPointer[min_i]);
			}
		}
		else
		{
			if (Insert(CLayer, P, key, DP))
			{
				//更新key的函数
				if (Path.Nempty())
				{
					update(Path.OUT(), Pathi.OUT(), key, DP);
				}
			}
		}
	}
	void LayerDataAdd(unsigned long DataPointer, DT key)
	{
		if (H == 0)
		{
			Master = new Pointer;
			Master->Dp = new LayerData;
			Insert(*(Master->Dp), DataPointer, key);
			H++;
		}
		else
		{
			LayerData& CLayer = *FIndLayerData(key);
			if (isfull(CLayer))
			{
				Pointer NLayer = Divide(CLayer, DataPointer, key);
				if (H == 1)
				{
					Pointer C(&CLayer);
					delete Master;
					Master = new Pointer(newLayer(C, CLayer.key[min_i], CLayer.DataPointer[min_i],
						NLayer, NLayer.Dp->key[min_i], NLayer.Dp->DataPointer[min_i]));
					H++;
				}
				else
				{
					update0(Path.Read0(), Pathi.Read0(), CLayer.key[min_i], CLayer.DataPointer[min_i]);
					LayerNAdd(NLayer, NLayer.Dp->key[min_i], NLayer.Dp->DataPointer[min_i]);
				}
			}
			else
			{
				if (Insert(CLayer, DataPointer, key))
				{
					//更新key的函数
					if (Path.Nempty())
					{
						update(Path.OUT(), Pathi.OUT(), key, DataPointer);
					}
				}
			}

		}
	}

	void LayerNDelete(DT key, unsigned long DP)
	{
		LayerN& CLayer = *Path.OUT();
		Pathi.OUT();
		DT keymax = CLayer.key[min_i];
		unsigned long DPmax = CLayer.DataPointer[min_i];
		int del = Delete(CLayer, key, DP);
		if (Path.Nempty())
		{
			if (CLayer.num < min_key)
			{
				LayerN& FNode = *Path.Read0();
				int Fi = Pathi.Read0();
				LayerN* BNode;
				int Bi;
				if (Fi == 0)
				{//右
					Bi = Fi + 1;
					BNode = FNode.NodePointer[Bi].Np;
					if (ismore(*BNode))//借用
					{
						int i = 0;
						Shift(*BNode, i, i, CLayer, min_i);
						update0(Path.OUT(), Pathi.OUT(), CLayer.key[min_i], CLayer.DataPointer[min_i]);
					}
					else//合并
					{
						MoveArray_b(BNode->key, 0, min_i, BNode->key, max_i);
						MoveArray_b(BNode->NodePointer, 0, min_i, BNode->NodePointer, max_i);
						MoveArray_b(BNode->DataPointer, 0, min_i, BNode->DataPointer, max_i);
						Shift(CLayer, 0, min_i - 1, *BNode, 0);
						LayerNDelete(keymax, DPmax);
						delete& CLayer;
					}
				}
				else
				{//左
					Bi = Fi - 1;
					BNode = FNode.NodePointer[Bi].Np;
					if (ismore(*BNode))//借用
					{
						int i = --BNode->num;
						Insert(CLayer, BNode->NodePointer[i], BNode->key[i], BNode->DataPointer[i]);
						update0(&FNode, Bi, BNode->key[i - 1], BNode->DataPointer[i - 1]);
					}
					else//合并
					{
						Shift(CLayer, 0, min_i - 1, *BNode, min_i + 1);
						update0(&FNode, Bi, BNode->key[max_i], BNode->DataPointer[max_i]);
						LayerNDelete(keymax, DPmax);
						delete& CLayer;
					}
				}
			}
			else if (del == CLayer.num)
			{
				update(Path.OUT(), Pathi.OUT(), CLayer.key[CLayer.num - 1], CLayer.DataPointer[CLayer.num - 1]);
			}
		}
		else if (CLayer.num == 1)
		{
			Pointer* NewMaster = new Pointer(CLayer.NodePointer[0]);
			delete Master->Np;
			delete Master;
			Master = NewMaster;
			H--;
		}

	}
	void LayerDataDelete(unsigned long DataPointer, DT key)
	{
		LayerData& CLayer = *FIndLayerData(key);
		DT keymax = CLayer.key[min_i];
		DT DPmax = CLayer.DataPointer[min_i];
		int del = Delete(CLayer, key);
		if (Path.Nempty())
		{
			if (CLayer.num < min_key)
			{
				LayerN& FNode = *Path.Read0();
				int Fi = Pathi.Read0();
				LayerData* BNode;
				int Bi;
				if (Fi == 0)
				{//右
					Bi = Fi + 1;
					BNode = FNode.NodePointer[Bi].Dp;
					if (ismore(*BNode))//借用
					{
						int i = BNode->num - 1;
						Shift(*BNode, i, i, CLayer, min_i);
						update0(Path.OUT(), Pathi.OUT(), CLayer.key[min_i], CLayer.DataPointer[min_i]);
					}
					else//合并
					{
						MoveArray_b(BNode->key, 0, min_i, BNode->key, max_i);
						MoveArray_b(BNode->DataPointer, 0, min_i, BNode->DataPointer, max_i);
						Shift(CLayer, 0, min_i - 1, *BNode, 0);
						LayerNDelete(keymax, DPmax);
						delete& CLayer;
					}
				}
				else
				{//左
					Bi = Fi - 1;
					BNode = FNode.NodePointer[Bi].Dp;
					if (ismore(*BNode))//借用
					{
						int i = --BNode->num;
						Insert(CLayer, BNode->DataPointer[i], BNode->key[i]);
						update0(&FNode, Bi, BNode->key[i - 1], BNode->DataPointer[i - 1]);
					}
					else//合并
					{
						Shift(CLayer, 0, min_i - 1, *BNode, min_i + 1);
						update0(&FNode, Bi, BNode->key[max_i], BNode->DataPointer[max_i]);
						LayerNDelete(keymax, DPmax);
						delete& CLayer;
					}
				}
			}
			else if (del == CLayer.num)
			{
				update(Path.OUT(), Pathi.OUT(), CLayer.key[CLayer.num - 1], CLayer.DataPointer[CLayer.num - 1]);
			}
		}
	}

public:
	void append(unsigned long DataPointer, DT key)
	{
		LayerDataAdd(DataPointer, key);
	}
	void data_delete(unsigned long DataPointer, DT key)
	{
		LayerDataDelete(DataPointer, key);
	}
	void data_find();
};

#endif // !INDEX_SINGLE_H


