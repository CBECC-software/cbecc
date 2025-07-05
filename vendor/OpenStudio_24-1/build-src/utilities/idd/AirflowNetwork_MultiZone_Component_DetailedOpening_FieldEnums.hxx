/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
Name, AirMassFlowCoefficientWhenOpeningisClosed, AirMassFlowExponentWhenOpeningisClosed, TypeofRectangularLargeVerticalOpening_LVO_, ExtraCrackLengthorHeightofPivotingAxis, NumberofSetsofOpeningFactorData,   };
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

/** \class AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:Component:DetailedOpening's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields, )
#else
class AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields: public ::EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields> {
 public: 
  enum domain 
  {
OpeningFactor, DischargeCoefficientforOpeningFactor, WidthFactorforOpeningFactor, HeightFactorforOpeningFactor, StartHeightFactorforOpeningFactor,   };
  AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields()
   : EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields>(OpeningFactor) {} 
  AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields>(t_name) {} 
  AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields>;
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
{ AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields::OpeningFactor, "OpeningFactor", "Opening Factor"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields::DischargeCoefficientforOpeningFactor, "DischargeCoefficientforOpeningFactor", "Discharge Coefficient for Opening Factor"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields::WidthFactorforOpeningFactor, "WidthFactorforOpeningFactor", "Width Factor for Opening Factor"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields::HeightFactorforOpeningFactor, "HeightFactorforOpeningFactor", "Height Factor for Opening Factor"},
{ AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields::StartHeightFactorforOpeningFactor, "StartHeightFactorforOpeningFactor", "Start Height Factor for Opening Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields> OptionalAirflowNetwork_MultiZone_Component_DetailedOpeningExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_COMPONENT_DETAILEDOPENING_FIELDENUMS_HXX
