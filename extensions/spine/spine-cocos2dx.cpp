/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated September 24, 2021. Replaces all prior versions.
 *
 * Copyright (c) 2013-2021, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THE SPINE RUNTIMES ARE PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,
 * BUSINESS INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THE SPINE RUNTIMES, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/Extension.h>
#include <spine/spine-cocos2dx.h>

USING_NS_CC;
using namespace spine;

Cocos2dAtlasAttachmentLoader::Cocos2dAtlasAttachmentLoader(Atlas *atlas) : AtlasAttachmentLoader(atlas) {
}

Cocos2dAtlasAttachmentLoader::~Cocos2dAtlasAttachmentLoader() {}

void Cocos2dAtlasAttachmentLoader::configureAttachment(Attachment *attachment) {
}


backend::SamplerAddressMode wrap(TextureWrap wrap) {
	return wrap == TextureWrap_ClampToEdge ? backend::SamplerAddressMode::CLAMP_TO_EDGE : backend::SamplerAddressMode::REPEAT;
}

backend::SamplerFilter filter(TextureFilter filter) {
	switch (filter) {
		case TextureFilter_Unknown:
			break;
		case TextureFilter_Nearest:
			return backend::SamplerFilter::NEAREST;
		case TextureFilter_Linear:
			return backend::SamplerFilter::LINEAR;
		case TextureFilter_MipMap:
			return backend::SamplerFilter::LINEAR;
		case TextureFilter_MipMapNearestNearest:
			return backend::SamplerFilter::NEAREST;
		case TextureFilter_MipMapLinearNearest:
			return backend::SamplerFilter::NEAREST;
		case TextureFilter_MipMapNearestLinear:
			return backend::SamplerFilter::LINEAR;
		case TextureFilter_MipMapLinearLinear:
			return backend::SamplerFilter::LINEAR;
	}
	return backend::SamplerFilter::LINEAR;
}


Cocos2dTextureLoader::Cocos2dTextureLoader() : TextureLoader() {}
Cocos2dTextureLoader::~Cocos2dTextureLoader() {}

void Cocos2dTextureLoader::load(AtlasPage &page, const spine::String &path) {
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(path.buffer());
	CCASSERT(texture != nullptr, "Invalid image");
	if (texture) {
		texture->retain();
		Texture2D::TexParams textureParams(filter(page.minFilter), filter(page.magFilter), wrap(page.uWrap), wrap(page.vWrap));
		texture->setTexParameters(textureParams);

		page.setRendererObject(texture);
		page.width = texture->getPixelsWide();
		page.height = texture->getPixelsHigh();
	}
}

void Cocos2dTextureLoader::unload(void *texture) {
	if (texture) {
		((Texture2D *) texture)->release();
	}
}


Cocos2dExtension::Cocos2dExtension() : DefaultSpineExtension() {}

Cocos2dExtension::~Cocos2dExtension() {}

char *Cocos2dExtension::_readFile(const spine::String &path, int *length) {
	Data data = FileUtils::getInstance()->getDataFromFile(path.buffer());
	if (data.isNull()) return nullptr;

		// avoid buffer overflow (int is shorter than ssize_t in certain platforms)
	ssize_t tmpLen;
	char *ret = (char *) data.takeBuffer(&tmpLen);
	*length = static_cast<int>(tmpLen);
	return ret;
}

SpineExtension *spine::getDefaultExtension() {
	return new Cocos2dExtension();
}
