#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(instance == nullptr);
	instance = this;
}

Texture& TextureHolder::GetTexture(std::string filename)
{
	// 1. filename key가 map에 있는지 검사
	// 2-1. 있을 때 찾아서 반환
	// 2-2. 없을 때 만들어서 map insert

	auto& map = instance->mapTexture;
	auto it = map.find(filename);
	if (it == map.end())
	{
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}

	return map[filename];

}
