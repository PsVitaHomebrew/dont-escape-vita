# Translating the game's C# scripts to C++

Source: `export/ExportedProject/Assets/Scripts/Assembly-CSharp/<Class>.cs` (decompiled by AssetRipper/ILSpy).
Target: `engine/src/game/cpp/<Class>.cpp`, one file per class.

The class **declarations are generated** (`engine/src/game/h/<Class>.h`, by `tools/gen/gen.js`). Don't edit headers. You write only the bodies.

## What a translated file contains
```cpp
#include "../game_all.h"

Foo::Foo() { ... }          // ONLY if h/Foo.h declares "Foo();" without a body
void Foo::Awake() { ... }   // every method/property the header declares (except the generated ones)
void Foo::_cctor() { ... }  // ONLY if the header declares _cctor(): set the statics marked "(set in _cctor)"
```
- Copy each signature exactly from the header (drop the default values in the .cpp).
- Never define `_load`, `_save`, `_clearRefs` or `_getClassInfo`; they're generated.
- A property `X` is declared as `get_X()` / `set_X(T value)`.
- Translate **literally**: same statements, same order, same names. Don't "improve" or simplify logic, and don't add comments.
- Check it compiles on its own: `cmd /c engine\check.bat Foo` (no errors allowed). Then run `node tools/gen/gen.js <cs dir> engine/src/game --chunks-only` so the build picks up the file.

## Types
| C# | C++ |
|---|---|
| `int float bool double byte char long` | `int float bool double uint8_t char16_t long long` |
| `string` | `String` (UTF-16, can be null) |
| any class (`GameObject`, `SpriteRenderer`, game classes) | `P<T>` (checked, ref-counted pointer, use `->`) |
| `Vector2/3/4 Color Rect Bounds RaycastHit2D AnimatorStateInfo` and the struct `KeyValueString` | plain values, fields with `.` |
| `List<T>` | `List<T>` handle: `List<T>::New()`, `.Count()`, `.Add`, `[i]` |
| `T[]` | `Array<T>`: `Array<T>::New(n)`, `Array<T>::Of({a, b})`, `.Length()` |
| enums | `enum class`. Nested ones are hoisted as `Outer_Name`, with alias `Outer::Name` inside the class |
| delegates / `Action` / lambdas | `std::function`; write lambdas as `[this]() { ... }` / `[=]() mutable { ... }` |

Locals: use `auto` or the mapped type. Generic methods: `GetComponent<T>()` stays the same.

## Null and references
- `x == null` → `x == nullptr`, `x != null` → `x != nullptr` (works for P, String, List, Array).
  Destroyed Unity objects count as null, as in Unity.
- C# `if (unityObj)` → `if (unityObj != nullptr)`.
- `x is T` → `x.is<T>()`; `x as T` → `x.as<T>()`; `(T)x` on a reference → `x.cast<T>()`.
- `base.M()` → `Base::M()`; `this.f` → `this->f` or just `f`.
- `new Foo()` (game class) → `New<Foo>()` (or `P<Foo>(new Foo())`).

## Strings (important)
- **Every** string literal: `"abc"` → `S("abc")`. Char literal: `'a'` → `u'a'`.
  `"abc" + 5` in C++ is pointer arithmetic, so the left side of a `+` chain must be a String.
- `string.Empty` → `String::Empty`; `string.IsNullOrEmpty(s)` → `String::IsNullOrEmpty(s)`.
- `+` concatenates String with int/float/bool/char16_t using C# formatting. Use `str(x)` where C# calls `x.ToString()` (numbers, bools, **enums → value name**).
- `s.Length` → `s.Length()`; `s[i]` is a `char16_t`; methods keep their names: `IndexOf Substring Replace Split ToLower ToUpper Trim StartsWith EndsWith Contains Equals CompareTo ToCharArray Insert Remove`.
- `new string(chars)` → `String::FromChars(chars)`; `string.Concat(a,b)` → `String::Concat(a,b)`; `int.Parse` → `int_Parse`; `float.Parse` → `float_Parse`; `char.ToLower` → `char_ToLower`.
- A `switch` on strings becomes an `if / else if` chain using `==`.

## Numbers
- `1f` → `1.0f`, `.5f` → `0.5f`, `2L` → `2LL`; float `%` → `std::fmod(a, b)`.
- `Mathf.X` → `Mathf::X` (Round/RoundToInt use banker's rounding like Unity); `Math.Round` → `Math_Round`; `Math.Abs` → `Math_Abs`.
- Keep every cast C# has (`(float)x`, `(int)f`). Integer division behaves the same.

## Unity API: properties become get_/set_
- `transform.position` → `transform->get_position()`; `transform.position = v` → `transform->set_position(v)`.
- `t.position += v` → `t->set_position(t->get_position() + v)`.
- The same pattern for `localPosition localScale parent enabled sprite color flipX flipY activeSelf name tag layer clip volume pitch loop isPlaying time speed orthographic orthographicSize cullingMask rect depth size offset isTrigger text texture width height pivot length normalizedTime collider`.
- **Fields, not properties:** `gameObject` and `transform` on components, `go->transform`. Value-type members (`v.x`, `c.a`, `r.width`) are plain fields too.
- Static classes use `::`, and static properties use getters:
  `Time.deltaTime` → `Time::get_deltaTime()`, `Camera.main` → `Camera::get_main()`, `Screen.width` → `Screen::get_width()`, `Input.mousePosition` → `Input::get_mousePosition()`, `Random.value` → `Random::get_value()`, `Application.persistentDataPath` → `Application::get_persistentDataPath()`, `Cursor.visible = b` → `Cursor::set_visible(b)`, `Application.targetFrameRate = n` → `Application::set_targetFrameRate(n)`, `AudioListener.volume = v` → `AudioListener::set_volume(v)`.
- Methods keep their names: `GameObject::Find(S("x"))`, `GameObject::FindGameObjectWithTag(...)`, `go->SetActive(b)`, `GetComponent<T>()`, `Resources::Load<T>(path)` (also for `(T)Resources.Load(path)` and `Resources.Load(path) as T`), `Resources::LoadAll<T>(path)`, `Object::Instantiate(x)` / `Object::Instantiate<T>(x)`, `Destroy(x)`, `DontDestroyOnLoad(x)`, `Invoke(S("m"), t)`, `InvokeRepeating`, `CancelInvoke()`, `SceneManager::LoadScene(...)`, `SceneManager::GetActiveScene().get_name()`, `PlayerPrefs::GetInt(...)`, `Input::GetKeyDown(KeyCode::Escape)`, `Input::GetMouseButtonDown(0)`, `Physics2D::LinecastAll(a, b)`, `anim->Play(S("x"))`, `audio->PlayOneShot(clip)`, `Debug::Log(...)`, `MonoBehaviour::print(...)`, `LayerMask::NameToLayer(...)`.
- Object initialisers `new Vector2 { x = a, y = b }` → declare, then assign (`Vector2 v; v.x = a; v.y = b;`). See `ScreenControler.cpp`.
- `new Vector3(1f, 2f, 0f)` → `Vector3(1.0f, 2.0f, 0.0f)`; `Vector3.zero` → `Vector3::get_zero()`; `Color.white` → `Color::get_white()`.
- `KeyCode.P` → `KeyCode::Pp`, `KeyCode.S` → `KeyCode::S_`. `RaycastHit2D` in an `if` → `if ((bool)hit)`; `hit.collider` → `hit.get_collider()`.

## Renamed identifiers
A field, local, parameter, method or enum value named `S alive P str New log NULL min max EOF TRUE FALSE ERROR` gets a trailing underscore (`S_`, `NULL_`, ...). The headers already use the new names.

## Statics, constructors
- `Foo.bar` (static) → `Foo::bar`.
- If the header has `static void _cctor();`, assign there the statics whose comment says "(set in _cctor)".
- If the header declares `Foo();` (no body): define it, and do every field initialiser marked "C# init: ... (do it in the constructor)" plus the C# constructor body. A base constructor call `: base(x)` goes in the initialiser list.

## Saving (GameDataController only)
`BinaryFormatter` and `File.Open` have stand-ins, so translate them literally:
`BinaryFormatter binaryFormatter;` `P<FileStream> fs = File::Open(path, FileMode::OpenOrCreate);` `binaryFormatter.Serialize(fs, data);` `P<SaveData> d = binaryFormatter.Deserialize<SaveData>(fs);` `fs->Close();`

## Store SDKs
Steam (`SteamManager`, `SteamUserStats`, `Steamworks.*`), GOG Galaxy and Kongregate/Kartridge don't exist on the Vita.
- Remove those calls.
- `SteamManager.Initialized` → `false`.
- A method that only does store work gets an empty body (or returns false/default).

## When the engine is missing something
If a call fails to compile because the engine has no such Unity/.NET member (not because of a translation mistake), don't edit engine files.
- For a statement, write `ENGINE_TODO("C# text of the call");`.
- For a value, write `ENGINE_TODO_V("C# text", fallback)`, where the fallback is the most harmless value.
- List each one in your report.

## Worked examples
See `engine/src/game/cpp/LoadingScene.cpp`, `StaticControler.cpp` and `Orthographic.cpp` next to their `.cs` files.
