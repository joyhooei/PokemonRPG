<GameProjectFile>
  <PropertyGroup Type="Node" Name="battle_player_board_2" ID="2aab1d9d-a150-436b-982c-da66f782a6d6" Version="2.3.1.1" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Node" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="board_bg" ActionTag="-786491580" Tag="3" IconVisible="False" LeftMargin="-150.0000" RightMargin="-150.0000" TopMargin="-30.0000" BottomMargin="-30.0000" Scale9Enable="True" LeftEage="16" RightEage="16" TopEage="16" BottomEage="16" Scale9OriginX="16" Scale9OriginY="16" Scale9Width="19" Scale9Height="19" ctype="ImageViewObjectData">
            <Size X="300.0000" Y="60.0000" />
            <Children>
              <AbstractNodeData Name="pokemon_name" ActionTag="1262623502" Tag="3" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="10.0000" RightMargin="168.0000" TopMargin="8.0000" BottomMargin="30.0000" FontSize="20" LabelText="我的名字很长" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ShadowEnabled="True" ctype="TextObjectData">
                <Size X="122.0000" Y="22.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="10.0000" Y="41.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0333" Y="0.6833" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="fonts/DFPYuanW7-GB.ttf" Plist="" />
                <OutlineColor A="255" R="0" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_gender" ActionTag="-1518966636" Tag="4" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="140.0000" RightMargin="150.0000" TopMargin="12.0000" BottomMargin="34.0000" ctype="SpriteObjectData">
                <Size X="10.0000" Y="14.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="145.0000" Y="41.0000" />
                <Scale ScaleX="1.2500" ScaleY="1.2500" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4833" Y="0.6833" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="common/icon_male.png" Plist="textures/common.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_state" ActionTag="-387411875" Tag="7" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="32.5000" RightMargin="242.5000" TopMargin="32.5001" BottomMargin="2.4999" ctype="SpriteObjectData">
                <Size X="25.0000" Y="25.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="45.0000" Y="14.9999" />
                <Scale ScaleX="0.7000" ScaleY="0.7000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.1500" Y="0.2500" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="common/icon_state_1.png" Plist="textures/common.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_ball" ActionTag="2115799280" Tag="25" IconVisible="False" HorizontalEdge="LeftEdge" VerticalEdge="TopEdge" LeftMargin="12.0000" RightMargin="272.0000" TopMargin="37.0000" BottomMargin="7.0000" ctype="SpriteObjectData">
                <Size X="16.0000" Y="16.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="20.0000" Y="15.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0667" Y="0.2500" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="common/ball_owning.png" Plist="textures/common.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="pokemon_lv" ActionTag="-408012991" Tag="8" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="TopEdge" LeftMargin="227.0000" RightMargin="15.0000" TopMargin="8.0000" BottomMargin="30.0000" FontSize="20" LabelText="Lv.100" HorizontalAlignmentType="HT_Right" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ShadowEnabled="True" ctype="TextObjectData">
                <Size X="58.0000" Y="22.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="285.0000" Y="41.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9500" Y="0.6833" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="fonts/DFPYuanW7-GB.ttf" Plist="" />
                <OutlineColor A="255" R="0" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="hp_back" ActionTag="188667858" Tag="10" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="TopEdge" LeftMargin="150.5000" RightMargin="10.5000" TopMargin="38.5000" BottomMargin="8.5000" ctype="SpriteObjectData">
                <Size X="139.0000" Y="13.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="220.0000" Y="15.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7333" Y="0.2500" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="common/hp_back.png" Plist="textures/common.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="hp_bar" ActionTag="1519541676" Tag="11" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="TopEdge" LeftMargin="152.0000" RightMargin="12.0000" TopMargin="40.0000" BottomMargin="10.0000" ProgressInfo="100" ctype="LoadingBarObjectData">
                <Size X="136.0000" Y="10.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="220.0000" Y="15.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7333" Y="0.2500" />
                <PreSize X="0.4533" Y="0.1000" />
                <ImageFileData Type="PlistSubImage" Path="common/hp_green.png" Plist="textures/common.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="hp_text" ActionTag="269599132" Tag="27" IconVisible="False" LeftMargin="124.0000" RightMargin="154.0000" TopMargin="37.0000" BottomMargin="5.0000" FontSize="16" LabelText="HP" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="22.0000" Y="18.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="135.0000" Y="14.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.4500" Y="0.2333" />
                <PreSize X="0.0000" Y="0.0000" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="common/back_gray.png" Plist="textures/common.plist" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>