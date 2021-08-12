#pragma once
#ifndef __ABSTRACT_FACTORY_H__
#define __ABSTRACT_FACTORY_H__


class Object;
template<typename T>
class AbstractFactory
{
public:
	static Object* Create()
	{
		Object* temp = new T;
		temp->ReadObject();

		return temp;
	}

	static Object* Create(D3DXVECTOR3 _pos)
	{
		Object* temp = new T;
		temp->ReadObject();
		temp->SetPos(_pos);

		return temp;
	}


	static Object* Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size)
	{
		Object* temp = new T;
		temp->ReadObject();
		temp->SetPos(_pos);
		temp->SetSize(_size);

		return temp;
	}


	static Object* Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size, D3DXVECTOR3 _dir)
	{
		Object* temp = new T;
		temp->ReadObject();
		temp->SetPos(_pos);
		temp->SetSize(_size);
		temp->SetDir(_dir);

		return temp;
	}


	static Object* Create(D3DXVECTOR3 _pos, D3DXVECTOR3 _size,
		D3DXVECTOR3 _dir, D3DXMATRIX _mat)
	{
		Object* temp = new T;
		temp->ReadObject();
		temp->SetPos(_pos);
		temp->SetSize(_size);
		temp->SetDir(_dir);
		temp->SetMat(_mat);

		return temp;
	}
};


#endif // !__ABSTRACT_FACTORY_H__