#ifndef I_BASE_H
#define I_BASE_H

namespace kp
{
	class IBase
	{
	public:
		virtual void update(float dT) = 0;
		virtual void render() = 0;
	};
}

#endif // !I_BASE_H