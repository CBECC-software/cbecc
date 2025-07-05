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

#ifndef UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_SLABGROUP_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_SLABGROUP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_VentilatedSlab_SlabGroupFields
 *  \brief Enumeration of ZoneHVAC:VentilatedSlab:SlabGroup's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_VentilatedSlab_SlabGroupFields, )
#else
class ZoneHVAC_VentilatedSlab_SlabGroupFields: public ::EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields> {
 public: 
  enum domain 
  {
Name,   };
  ZoneHVAC_VentilatedSlab_SlabGroupFields()
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>(Name) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>(t_name) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupFields(int t_value) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_VentilatedSlab_SlabGroupFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupFields>;
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
{ ZoneHVAC_VentilatedSlab_SlabGroupFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_VentilatedSlab_SlabGroupFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_VentilatedSlab_SlabGroupFields> OptionalZoneHVAC_VentilatedSlab_SlabGroupFields ;
#endif

/** \class ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields
 *  \brief Enumeration of ZoneHVAC:VentilatedSlab:SlabGroup's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields, )
#else
class ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields: public ::EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields> {
 public: 
  enum domain 
  {
ZoneName, SurfaceName, CoreDiameterforSurface, CoreLengthforSurface, CoreNumbersforSurface, SlabInletNodeNameforSurface, SlabOutletNodeNameforSurface,   };
  ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields()
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>(ZoneName) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>(t_name) {} 
  ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields>;
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
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::CoreDiameterforSurface, "CoreDiameterforSurface", "Core Diameter for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::CoreLengthforSurface, "CoreLengthforSurface", "Core Length for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::CoreNumbersforSurface, "CoreNumbersforSurface", "Core Numbers for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::SlabInletNodeNameforSurface, "SlabInletNodeNameforSurface", "Slab Inlet Node Name for Surface"},
{ ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields::SlabOutletNodeNameforSurface, "SlabOutletNodeNameforSurface", "Slab Outlet Node Name for Surface"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields> OptionalZoneHVAC_VentilatedSlab_SlabGroupExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_SLABGROUP_FIELDENUMS_HXX
