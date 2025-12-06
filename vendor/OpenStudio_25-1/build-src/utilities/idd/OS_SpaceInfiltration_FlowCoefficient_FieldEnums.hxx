/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SPACEINFILTRATION_FLOWCOEFFICIENT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SPACEINFILTRATION_FLOWCOEFFICIENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SpaceInfiltration_FlowCoefficientFields
 *  \brief Enumeration of OS:SpaceInfiltration:FlowCoefficient's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SpaceInfiltration_FlowCoefficientFields, )
#else
class OS_SpaceInfiltration_FlowCoefficientFields: public ::EnumBase<OS_SpaceInfiltration_FlowCoefficientFields> {
 public: 
  enum domain 
  {
Handle, Name, SpaceorSpaceTypeName, ScheduleName, FlowCoefficient, StackCoefficient, PressureExponent, WindCoefficient, ShelterFactor,   };
  OS_SpaceInfiltration_FlowCoefficientFields()
   : EnumBase<OS_SpaceInfiltration_FlowCoefficientFields>(Handle) {} 
  OS_SpaceInfiltration_FlowCoefficientFields(const std::string &t_name) 
   : EnumBase<OS_SpaceInfiltration_FlowCoefficientFields>(t_name) {} 
  OS_SpaceInfiltration_FlowCoefficientFields(int t_value) 
   : EnumBase<OS_SpaceInfiltration_FlowCoefficientFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SpaceInfiltration_FlowCoefficientFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SpaceInfiltration_FlowCoefficientFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SpaceInfiltration_FlowCoefficientFields>;
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
{ OS_SpaceInfiltration_FlowCoefficientFields::Handle, "Handle", "Handle"},
{ OS_SpaceInfiltration_FlowCoefficientFields::Name, "Name", "Name"},
{ OS_SpaceInfiltration_FlowCoefficientFields::SpaceorSpaceTypeName, "SpaceorSpaceTypeName", "Space or SpaceType Name"},
{ OS_SpaceInfiltration_FlowCoefficientFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_SpaceInfiltration_FlowCoefficientFields::FlowCoefficient, "FlowCoefficient", "Flow Coefficient"},
{ OS_SpaceInfiltration_FlowCoefficientFields::StackCoefficient, "StackCoefficient", "Stack Coefficient"},
{ OS_SpaceInfiltration_FlowCoefficientFields::PressureExponent, "PressureExponent", "Pressure Exponent"},
{ OS_SpaceInfiltration_FlowCoefficientFields::WindCoefficient, "WindCoefficient", "Wind Coefficient"},
{ OS_SpaceInfiltration_FlowCoefficientFields::ShelterFactor, "ShelterFactor", "Shelter Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SpaceInfiltration_FlowCoefficientFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SpaceInfiltration_FlowCoefficientFields> OptionalOS_SpaceInfiltration_FlowCoefficientFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SPACEINFILTRATION_FLOWCOEFFICIENT_FIELDENUMS_HXX
