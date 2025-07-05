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

#ifndef UTILITIES_IDD_DEMANDMANAGER_EXTERIORLIGHTS_FIELDENUMS_HXX
#define UTILITIES_IDD_DEMANDMANAGER_EXTERIORLIGHTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DemandManager_ExteriorLightsFields
 *  \brief Enumeration of DemandManager:ExteriorLights's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DemandManager_ExteriorLightsFields, )
#else
class DemandManager_ExteriorLightsFields: public ::EnumBase<DemandManager_ExteriorLightsFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, LimitControl, MinimumLimitDuration, MaximumLimitFraction, LimitStepChange, SelectionControl, RotationDuration,   };
  DemandManager_ExteriorLightsFields()
   : EnumBase<DemandManager_ExteriorLightsFields>(Name) {} 
  DemandManager_ExteriorLightsFields(const std::string &t_name) 
   : EnumBase<DemandManager_ExteriorLightsFields>(t_name) {} 
  DemandManager_ExteriorLightsFields(int t_value) 
   : EnumBase<DemandManager_ExteriorLightsFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ExteriorLightsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ExteriorLightsFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ExteriorLightsFields>;
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
{ DemandManager_ExteriorLightsFields::Name, "Name", "Name"},
{ DemandManager_ExteriorLightsFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ DemandManager_ExteriorLightsFields::LimitControl, "LimitControl", "Limit Control"},
{ DemandManager_ExteriorLightsFields::MinimumLimitDuration, "MinimumLimitDuration", "Minimum Limit Duration"},
{ DemandManager_ExteriorLightsFields::MaximumLimitFraction, "MaximumLimitFraction", "Maximum Limit Fraction"},
{ DemandManager_ExteriorLightsFields::LimitStepChange, "LimitStepChange", "Limit Step Change"},
{ DemandManager_ExteriorLightsFields::SelectionControl, "SelectionControl", "Selection Control"},
{ DemandManager_ExteriorLightsFields::RotationDuration, "RotationDuration", "Rotation Duration"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ExteriorLightsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ExteriorLightsFields> OptionalDemandManager_ExteriorLightsFields ;
#endif

/** \class DemandManager_ExteriorLightsExtensibleFields
 *  \brief Enumeration of DemandManager:ExteriorLights's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(DemandManager_ExteriorLightsExtensibleFields, )
#else
class DemandManager_ExteriorLightsExtensibleFields: public ::EnumBase<DemandManager_ExteriorLightsExtensibleFields> {
 public: 
  enum domain 
  {
ExteriorLightsName,   };
  DemandManager_ExteriorLightsExtensibleFields()
   : EnumBase<DemandManager_ExteriorLightsExtensibleFields>(ExteriorLightsName) {} 
  DemandManager_ExteriorLightsExtensibleFields(const std::string &t_name) 
   : EnumBase<DemandManager_ExteriorLightsExtensibleFields>(t_name) {} 
  DemandManager_ExteriorLightsExtensibleFields(int t_value) 
   : EnumBase<DemandManager_ExteriorLightsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ExteriorLightsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ExteriorLightsExtensibleFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ExteriorLightsExtensibleFields>;
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
{ DemandManager_ExteriorLightsExtensibleFields::ExteriorLightsName, "ExteriorLightsName", "Exterior Lights Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ExteriorLightsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ExteriorLightsExtensibleFields> OptionalDemandManager_ExteriorLightsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEMANDMANAGER_EXTERIORLIGHTS_FIELDENUMS_HXX
