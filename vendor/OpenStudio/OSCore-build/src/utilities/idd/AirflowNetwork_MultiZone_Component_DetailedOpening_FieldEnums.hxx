/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_COMPONENT_DETAILEDOPENING_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_COMPONENT_DETAILEDOPENING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_Component_DetailedOpeningFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:Component:DetailedOpening's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_Component_DetailedOpeningFields, )
#else
class AirflowNetwork_MultiZone_Component_DetailedOpeningFields: public ::EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningFields> {
 public: 
  enum domain 
  {
Name, AirMassFlowCoefficientWhenOpeningisClosed, AirMassFlowExponentWhenOpeningisClosed, TypeofRectangularLargeVerticalOpening_LVO_, ExtraCrackLengthorHeightofPivotingAxis, NumberofSetsofOpeningFactorData, OpeningFactor1, DischargeCoefficientforOpeningFactor1, WidthFactorforOpeningFactor1, HeightFactorforOpeningFactor1, StartHeightFactorforOpeningFactor1, OpeningFactor2, DischargeCoefficientforOpeningFactor2, WidthFactorforOpeningFactor2, HeightFactorforOpeningFactor2, StartHeightFactorforOpeningFactor2, OpeningFactor3, DischargeCoefficientforOpeningFactor3, WidthFactorforOpeningFactor3, HeightFactorforOpeningFactor3, StartHeightFactorforOpeningFactor3, OpeningFactor4, DischargeCoefficientforOpeningFactor4, WidthFactorforOpeningFactor4, HeightFactorforOpeningFactor4, StartHeightFactorforOpeningFactor4,   };
  AirflowNetwork_MultiZone_Component_DetailedOpeningFields()
   : EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningFields>(Name) {} 
  AirflowNetwork_MultiZone_Component_DetailedOpeningFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningFields>(t_name) {} 
  AirflowNetwork_MultiZone_Component_DetailedOpeningFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_Component_DetailedOpeningFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningFields>;
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
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::Name, "Name", "Name"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, "AirMassFlowCoefficientWhenOpeningisClosed", "Air Mass Flow Coefficient When Opening is Closed"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::AirMassFlowExponentWhenOpeningisClosed, "AirMassFlowExponentWhenOpeningisClosed", "Air Mass Flow Exponent When Opening is Closed"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::TypeofRectangularLargeVerticalOpening_LVO_, "TypeofRectangularLargeVerticalOpening_LVO_", "Type of Rectangular Large Vertical Opening (LVO)"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::ExtraCrackLengthorHeightofPivotingAxis, "ExtraCrackLengthorHeightofPivotingAxis", "Extra Crack Length or Height of Pivoting Axis"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::NumberofSetsofOpeningFactorData, "NumberofSetsofOpeningFactorData", "Number of Sets of Opening Factor Data"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::OpeningFactor1, "OpeningFactor1", "Opening Factor 1"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::DischargeCoefficientforOpeningFactor1, "DischargeCoefficientforOpeningFactor1", "Discharge Coefficient for Opening Factor 1"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::WidthFactorforOpeningFactor1, "WidthFactorforOpeningFactor1", "Width Factor for Opening Factor 1"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::HeightFactorforOpeningFactor1, "HeightFactorforOpeningFactor1", "Height Factor for Opening Factor 1"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::StartHeightFactorforOpeningFactor1, "StartHeightFactorforOpeningFactor1", "Start Height Factor for Opening Factor 1"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::OpeningFactor2, "OpeningFactor2", "Opening Factor 2"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::DischargeCoefficientforOpeningFactor2, "DischargeCoefficientforOpeningFactor2", "Discharge Coefficient for Opening Factor 2"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::WidthFactorforOpeningFactor2, "WidthFactorforOpeningFactor2", "Width Factor for Opening Factor 2"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::HeightFactorforOpeningFactor2, "HeightFactorforOpeningFactor2", "Height Factor for Opening Factor 2"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::StartHeightFactorforOpeningFactor2, "StartHeightFactorforOpeningFactor2", "Start Height Factor for Opening Factor 2"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::OpeningFactor3, "OpeningFactor3", "Opening Factor 3"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::DischargeCoefficientforOpeningFactor3, "DischargeCoefficientforOpeningFactor3", "Discharge Coefficient for Opening Factor 3"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::WidthFactorforOpeningFactor3, "WidthFactorforOpeningFactor3", "Width Factor for Opening Factor 3"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::HeightFactorforOpeningFactor3, "HeightFactorforOpeningFactor3", "Height Factor for Opening Factor 3"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::StartHeightFactorforOpeningFactor3, "StartHeightFactorforOpeningFactor3", "Start Height Factor for Opening Factor 3"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::OpeningFactor4, "OpeningFactor4", "Opening Factor 4"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::DischargeCoefficientforOpeningFactor4, "DischargeCoefficientforOpeningFactor4", "Discharge Coefficient for Opening Factor 4"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::WidthFactorforOpeningFactor4, "WidthFactorforOpeningFactor4", "Width Factor for Opening Factor 4"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::HeightFactorforOpeningFactor4, "HeightFactorforOpeningFactor4", "Height Factor for Opening Factor 4"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningFields::StartHeightFactorforOpeningFactor4, "StartHeightFactorforOpeningFactor4", "Start Height Factor for Opening Factor 4"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_Component_DetailedOpeningFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_Component_DetailedOpeningFields> OptionalAirflowNetwork_MultiZone_Component_DetailedOpeningFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_COMPONENT_DETAILEDOPENING_FIELDENUMS_HXX
