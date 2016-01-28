#ifndef ___DATA_CONFIG_JSON_AZP526YZQHE3766R
#define ___DATA_CONFIG_JSON_AZP526YZQHE3766R
namespace static_port____data_config
{
template <class T = std::string, class U = int>
struct json
{
  typedef T string_type;
  typedef U number_type;
  string_type _path = "build/result.json";
  template<class V>
  void traverse(V & h)
  {
    h( "path", _path);
  }
};
}
#endif