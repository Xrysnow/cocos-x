# RefPtr conversion

`cocos2d::RefPtr<T>` uses the same Lua userdata, inheritance checks and identity
cache as `T*`. There is no Lua RefPtr class. Include `lua_conversion.hpp` as for
other cocos conversions.

```cpp
void setTexture(cocos2d::RefPtr<cocos2d::Texture2D> texture);
bool acceptsTexture(const cocos2d::RefPtr<cocos2d::Texture2D>& texture);
cocos2d::RefPtr<cocos2d::Texture2D> getTexture();
```

- Lua `nil` converts to an empty RefPtr, and an empty RefPtr returns `nil`.
- A valid userdata (including a derived type or a `.c_instance` wrapper) is
  retained by the converted parameter. Failed conversion leaves the destination
  unchanged. Object validation remains enabled with `CC_LUA_BINDING_CHECKS=0`.
- By-value and const lvalue-reference parameters are supported. Mutable
  lvalue-reference and rvalue-reference parameters require an explicit adapter;
  Lua has no smart-pointer slot to update or move from.
- Nonempty output adds one independent retain/autorelease pair before pushing
  the existing object userdata. This keeps sole-owner temporary results alive
  until the current autorelease pool drains. The source RefPtr is not consumed.
  Repeated returns and objects already in an autorelease pool are balanced.
- Returning a const reference to a RefPtr uses the same output policy. Pointee
  constness follows the existing `const T*` binding convention; it does not
  create a read-only Lua object.
- This does not give Lua variables persistent native ownership. Objects needed
  after pool cleanup still require an engine owner or an explicit retain.
  Conversion runs on the scripting thread with the normal autorelease pool.

Bindings whose overloads differ only between `T*` and `RefPtr<T>` have the same
Lua representation; use an explicit adapter or expose only one overload.
