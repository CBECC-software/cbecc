/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKDETAILEDOPENING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKDETAILEDOPENING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkDetailedOpeningFields
 *  \brief Enumeration of OS:AirflowNetworkDetailedOpening's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkDetailedOpeningFields, )
#else
class OS_AirflowNetworkDetailedOpeningFields: public ::EnumBase<OS_AirflowNetworkDetailedOpeningFields> {
 public: 
  enum domain 
  {
Handle, Name, AirMassFlowCoefficientWhenOpeningisClosed, AirMassFlowExponentWhenOpeningisClosed, TypeofRectangularLargeVerticalOpening, ExtraCrackLengthorHeightofPivotingAxis,   };
  OS_AirflowNetworkDetailedOpeningFields()
   : EnumBase<OS_AirflowNetworkDetailedOpeningFields>(Handle) {} 
  OS_AirflowNetworkDetailedOpeningFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkDetailedOpeningFields>(t_name) {} 
  OS_AirflowNetworkDetailedOpeningFields(int t_value) 
   : EnumBase<OS_AirflowNetworkDetailedOpeningFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkDetailedOpeningFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkDetailedOpeningFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkDetailedOpeningFields>;
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
{ OS_AirflowNetworkDetailedOpeningFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkDetailedOpeningFields::Name, "Name", "Name"},
{ OS_AirflowNetworkDetailedOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, "AirMassFlowCoefficientWhenOpeningisClosed", "Air Mass Flow Coefficient When Opening is Closed"},
{ OS_AirflowNetworkDetailedOpeningFields::AirMassFlowExponentWhenOpeningisClosed, "AirMassFlowExponentWhenOpeningisClosed", "Air Mass Flow Exponent When Opening is Closed"},
{ OS_AirflowNetworkDetailedOpeningFields::TypeofRectangularLargeVerticalOpening, "TypeofRectangularLargeVerticalOpening", "Type of Rectangular Large Vertical Opening"},
{ OS_AirflowNetworkDetailedOpeningFields::ExtraCrackLengthorHeightofPivotingAxis, "ExtraCrackLengthorHeightofPivotingAxis", "Extra Crack Length or Height of Pivoting Axis"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkDetailedOpeningFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkDetailedOpeningFields> OptionalOS_AirflowNetworkDetailedOpeningFields ;
#endif

/** \class OS_AirflowNetworkDetailedOpeningExtensibleFields
 *  \brief Enumeration of OS:AirflowNetworkDetailedOpening's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_AirflowNetworkDetailedOpeningExtensibleFields, )
#else
class OS_AirflowNetworkDetailedOpeningExtensibleFields: public ::EnumBase<OS_AirflowNetworkDetailedOpeningExtensibleFields> {
 public: 
  enum domain 
  {
OpeningFactor, DischargeCoefficientforOpeningFactor, WidthFactorforOpeningFactor, HeightFactorforOpeningFactor, StartHeightFactorforOpeningFactor,   };
  OS_AirflowNetworkDetailedOpeningExtensibleFields()
   : EnumBase<OS_AirflowNetworkDetailedOpeningExtensibleFields>(OpeningFactor) {} 
  OS_AirflowNetworkDetailedOpeningExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkDetailedOpeningExtensibleFields>(t_name) {} 
  OS_AirflowNetworkDetailedOpeningExtensibleFields(int t_value) 
   : EnumBase<OS_AirflowNetworkDetailedOpeningExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkDetailedOpeningExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkDetailedOpeningExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkDetailedOpeningExtensibleFields>;
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
{ OS_AirflowNetworkDetailedOpeningExtensibleFields::OpeningFactor, "OpeningFactor", "Opening Factor"},
{ OS_AirflowNetworkDetailedOpeningExtensibleFields::DischargeCoefficientforOpeningFactor, "DischargeCoefficientforOpeningFactor", "Discharge Coefficient for Opening Factor"},
{ OS_AirflowNetworkDetailedOpeningExtensibleFields::WidthFactorforOpeningFactor, "WidthFactorforOpeningFactor", "Width Factor for Opening Factor"},
{ OS_AirflowNetworkDetailedOpeningExtensibleFields::HeightFactorforOpeningFactor, "HeightFactorforOpeningFactor", "Height Factor for Opening Factor"},
{ OS_AirflowNetworkDetailedOpeningExtensibleFields::StartHeightFactorforOpeningFactor, "StartHeightFactorforOpeningFactor", "Start Height Factor for Opening Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkDetailedOpeningExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkDetailedOpeningExtensibleFields> OptionalOS_AirflowNetworkDetailedOpeningExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKDETAILEDOPENING_FIELDENUMS_HXX
