<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/2000/svg" version="1.0">
  <xsl:output method="xml" indent="yes"/>
  <xsl:variable name="minlon" select="/osm/bounds/@minlon"/>
  <xsl:variable name="minlat" select="/osm/bounds/@minlat"/>
  <xsl:variable name="maxlat" select="/osm/bounds/@maxlat"/>
  <xsl:strip-space elements="*"/>
  <xsl:key name="nodeById" match="/osm/node" use="@id"/>
  <xsl:template match="osm">
     <svg version="1.1" width="20cm" height="10cm">
      <xsl:attribute name="viewBox">
	<xsl:apply-templates select="bounds"/>
      </xsl:attribute>
      <xsl:apply-templates select="//way[tag[(@k='building')and(@v='yes')]]"/>
    </svg>
  </xsl:template>
  <xsl:template match="bounds">
    <xsl:text>0 0 </xsl:text>
    <xsl:value-of select="round(@maxlon  * 8000 - $minlon  * 8000)"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="round(@maxlat  * 10000 - $minlat  * 10000)"/>
  </xsl:template>
  <xsl:template match="way">
    <polygon fill="red" stroke="blue" stroke-width="1">
      <xsl:attribute name="points">
	<xsl:apply-templates select="nd"/>
      </xsl:attribute>
    </polygon>
  </xsl:template>
  <xsl:template match="nd">
     <xsl:apply-templates select="key('nodeById',@ref)"/>	   
  </xsl:template>
  <xsl:template match="node">
       <xsl:value-of select="round(@lon * 8000 - $minlon  * 8000)"/>
       <xsl:text>,</xsl:text>
       <xsl:value-of select="round($maxlat  * 10000 - @lat * 10000)"/>
       <xsl:text> </xsl:text>		
  </xsl:template>
 </xsl:stylesheet>	
