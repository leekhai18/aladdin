#ifndef __FOREGROUND_PREFAB_H__
#define __FOREGROUND_PREFAB_H__

/*
* Created by Khuongnb1997 on Oct 17th 2017
*/

#include <aladdin.h>

class ForegroundPrefab : public ala::Prefab {
public:
	ForegroundPrefab() : Prefab("Foreground") {  }

	void doInstantiate(ala::GameObject* object) override;
};

#endif //!__FOREGROUND_PREFAB_H__
#pragma once
