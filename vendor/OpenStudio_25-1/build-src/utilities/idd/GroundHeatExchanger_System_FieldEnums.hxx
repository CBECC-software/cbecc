/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_SYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_SYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_SystemFields
 *  \brief Enumeration of GroundHeatExchanger:System's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_SystemFields, )
#else
class GroundHeatExchanger_SystemFields: public ::EnumBase<GroundHeatExchanger_SystemFields> {
 public: 
  enum domain 
  {
Name, InletNodeName, OutletNodeName, DesignFlowRate, UndisturbedGroundTemperatureModelType, UndisturbedGroundTemperatureModelName, GroundThermalConductivity, GroundThermalHeatCapacity, GHE_Vertical_ResponseFactorsObjectName, gFunctionCalculationMethod, GHE_Vertical_ArrayObjectName,   };
  GroundHeatExchanger_SystemFields()
   : EnumBase<GroundHeatExchanger_SystemFields>(Name) {} 
  GroundHeatExchanger_SystemFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_SystemFields>(t_name) {} 
  GroundHeatExchanger_SystemFields(int t_value) 
   : EnumBase<GroundHeatExchanger_SystemFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_SystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_SystemFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_SystemFields>;
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
{ GroundHeatExchanger_SystemFields::Name, "Name", "Name"},
{ GroundHeatExchanger_SystemFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ GroundHeatExchanger_SystemFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ GroundHeatExchanger_SystemFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType, "UndisturbedGroundTemperatureModelType", "Undisturbed Ground Temperature Model Type"},
{ GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelName, "UndisturbedGroundTemperatureModelName", "Undisturbed Ground Temperature Model Name"},
{ GroundHeatExchanger_SystemFields::GroundThermalConductivity, "GroundThermalConductivity", "Ground Thermal Conductivity"},
{ GroundHeatExchanger_SystemFields::GroundThermalHeatCapacity, "GroundThermalHeatCapacity", "Ground Thermal Heat Capacity"},
{ GroundHeatExchanger_SystemFields::GHE_Vertical_ResponseFactorsObjectName, "GHE_Vertical_ResponseFactorsObjectName", "GHE:Vertical:ResponseFactors Object Name"},
{ GroundHeatExchanger_SystemFields::gFunctionCalculationMethod, "gFunctionCalculationMethod", "g-Function Calculation Method"},
{ GroundHeatExchanger_SystemFields::GHE_Vertical_ArrayObjectName, "GHE_Vertical_ArrayObjectName", "GHE:Vertical:Array Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_SystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_SystemFields> OptionalGroundHeatExchanger_SystemFields ;
#endif

/** \class GroundHeatExchanger_SystemExtensibleFields
 *  \brief Enumeration of GroundHeatExchanger:System's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_SystemExtensibleFields, )
#else
class GroundHeatExchanger_SystemExtensibleFields: public ::EnumBase<GroundHeatExchanger_SystemExtensibleFields> {
 public: 
  enum domain 
  {
GHE_Vertical_SingleObjectName,   };
  GroundHeatExchanger_SystemExtensibleFields()
   : EnumBase<GroundHeatExchanger_SystemExtensibleFields>(GHE_Vertical_SingleObjectName) {} 
  GroundHeatExchanger_SystemExtensibleFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_SystemExtensibleFields>(t_name) {} 
  GroundHeatExchanger_SystemExtensibleFields(int t_value) 
   : EnumBase<GroundHeatExchanger_SystemExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_SystemExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_SystemExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_SystemExtensibleFields>;
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
{ GroundHeatExchanger_SystemExtensibleFields::GHE_Vertical_SingleObjectName, "GHE_Vertical_SingleObjectName", "GHE:Vertical:Single Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_SystemExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_SystemExtensibleFields> OptionalGroundHeatExchanger_SystemExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_SYSTEM_FIELDENUMS_HXX
