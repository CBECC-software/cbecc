/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_SINGLE_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_SINGLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_Vertical_SingleFields
 *  \brief Enumeration of GroundHeatExchanger:Vertical:Single's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_Vertical_SingleFields, )
#else
class GroundHeatExchanger_Vertical_SingleFields: public ::EnumBase<GroundHeatExchanger_Vertical_SingleFields> {
 public: 
  enum domain 
  {
Name, GHE_Vertical_PropertiesObjectName, XLocation, YLocation,   };
  GroundHeatExchanger_Vertical_SingleFields()
   : EnumBase<GroundHeatExchanger_Vertical_SingleFields>(Name) {} 
  GroundHeatExchanger_Vertical_SingleFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_Vertical_SingleFields>(t_name) {} 
  GroundHeatExchanger_Vertical_SingleFields(int t_value) 
   : EnumBase<GroundHeatExchanger_Vertical_SingleFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_Vertical_SingleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_Vertical_SingleFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_Vertical_SingleFields>;
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
{ GroundHeatExchanger_Vertical_SingleFields::Name, "Name", "Name"},
{ GroundHeatExchanger_Vertical_SingleFields::GHE_Vertical_PropertiesObjectName, "GHE_Vertical_PropertiesObjectName", "GHE:Vertical:Properties Object Name"},
{ GroundHeatExchanger_Vertical_SingleFields::XLocation, "XLocation", "X-Location"},
{ GroundHeatExchanger_Vertical_SingleFields::YLocation, "YLocation", "Y-Location"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_Vertical_SingleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_Vertical_SingleFields> OptionalGroundHeatExchanger_Vertical_SingleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_VERTICAL_SINGLE_FIELDENUMS_HXX
