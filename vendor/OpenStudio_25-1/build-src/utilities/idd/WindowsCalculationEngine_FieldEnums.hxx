/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_WINDOWSCALCULATIONENGINE_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWSCALCULATIONENGINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowsCalculationEngineFields
 *  \brief Enumeration of WindowsCalculationEngine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowsCalculationEngineFields, )
#else
class WindowsCalculationEngineFields: public ::EnumBase<WindowsCalculationEngineFields> {
 public: 
  enum domain 
  {
Windowsengine,   };
  WindowsCalculationEngineFields()
   : EnumBase<WindowsCalculationEngineFields>(Windowsengine) {} 
  WindowsCalculationEngineFields(const std::string &t_name) 
   : EnumBase<WindowsCalculationEngineFields>(t_name) {} 
  WindowsCalculationEngineFields(int t_value) 
   : EnumBase<WindowsCalculationEngineFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowsCalculationEngineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowsCalculationEngineFields>::integer_value()); }
   private:
    friend class EnumBase<WindowsCalculationEngineFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ WindowsCalculationEngineFields::Windowsengine, "Windowsengine", "Windows engine"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const WindowsCalculationEngineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowsCalculationEngineFields> OptionalWindowsCalculationEngineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWSCALCULATIONENGINE_FIELDENUMS_HXX
