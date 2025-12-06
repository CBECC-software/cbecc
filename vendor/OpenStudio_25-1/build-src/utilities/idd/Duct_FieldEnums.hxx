/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_DUCT_FIELDENUMS_HXX
#define UTILITIES_IDD_DUCT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DuctFields
 *  \brief Enumeration of Duct's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DuctFields, )
#else
class DuctFields: public ::EnumBase<DuctFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName,   };
  DuctFields()
   : EnumBase<DuctFields>(Name) {} 
  DuctFields(const std::string &t_name) 
   : EnumBase<DuctFields>(t_name) {} 
  DuctFields(int t_value) 
   : EnumBase<DuctFields>(t_value) {} 
  static std::string enumName() 
  { return "DuctFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DuctFields>::integer_value()); }
   private:
    friend class EnumBase<DuctFields>;
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
{ DuctFields::Name, "Name", "Name"},
{ DuctFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ DuctFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DuctFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DuctFields> OptionalDuctFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DUCT_FIELDENUMS_HXX
