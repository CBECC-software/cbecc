/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_RESPONSEFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_RESPONSEFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_ResponseFactorsFields
 *  \brief Enumeration of GroundHeatExchanger:ResponseFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_ResponseFactorsFields, )
#else
class GroundHeatExchanger_ResponseFactorsFields: public ::EnumBase<GroundHeatExchanger_ResponseFactorsFields> {
 public: 
  enum domain 
  {
Name, GHE_Vertical_PropertiesObjectName, NumberofBoreholes, GFunctionReferenceRatio,   };
  GroundHeatExchanger_ResponseFactorsFields()
   : EnumBase<GroundHeatExchanger_ResponseFactorsFields>(Name) {} 
  GroundHeatExchanger_ResponseFactorsFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsFields>(t_name) {} 
  GroundHeatExchanger_ResponseFactorsFields(int t_value) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_ResponseFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_ResponseFactorsFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_ResponseFactorsFields>;
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
{ GroundHeatExchanger_ResponseFactorsFields::Name, "Name", "Name"},
{ GroundHeatExchanger_ResponseFactorsFields::GHE_Vertical_PropertiesObjectName, "GHE_Vertical_PropertiesObjectName", "GHE:Vertical:Properties Object Name"},
{ GroundHeatExchanger_ResponseFactorsFields::NumberofBoreholes, "NumberofBoreholes", "Number of Boreholes"},
{ GroundHeatExchanger_ResponseFactorsFields::GFunctionReferenceRatio, "GFunctionReferenceRatio", "G-Function Reference Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_ResponseFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_ResponseFactorsFields> OptionalGroundHeatExchanger_ResponseFactorsFields ;
#endif

/** \class GroundHeatExchanger_ResponseFactorsExtensibleFields
 *  \brief Enumeration of GroundHeatExchanger:ResponseFactors's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(GroundHeatExchanger_ResponseFactorsExtensibleFields, )
#else
class GroundHeatExchanger_ResponseFactorsExtensibleFields: public ::EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields> {
 public: 
  enum domain 
  {
gFunctionLn_T_Ts_Value, gFunctiongValue,   };
  GroundHeatExchanger_ResponseFactorsExtensibleFields()
   : EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>(gFunctionLn_T_Ts_Value) {} 
  GroundHeatExchanger_ResponseFactorsExtensibleFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>(t_name) {} 
  GroundHeatExchanger_ResponseFactorsExtensibleFields(int t_value) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_ResponseFactorsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>;
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
{ GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctionLn_T_Ts_Value, "gFunctionLn_T_Ts_Value", "g-Function Ln(T/Ts) Value"},
{ GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctiongValue, "gFunctiongValue", "g-Function g Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_ResponseFactorsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_ResponseFactorsExtensibleFields> OptionalGroundHeatExchanger_ResponseFactorsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_RESPONSEFACTORS_FIELDENUMS_HXX
