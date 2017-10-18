#ifndef __BACKGROUND_PREFAB_H__
#define __BACKGROUND_PREFAB_H__

/*
* Created by Khuongnb1997 on Oct 17th 2017
*/

#include <aladdin.h>

class BackgroundPrefab : public ala::Prefab {
public:
	BackgroundPrefab(): Prefab("Background") {  }

	void doInstantiate(ala::GameObject* object) override;
};

#endif //!__BACKGROUND_PREFAB_H__
