<GameProjectFile>
  <PropertyGroup Type="Node" Name="battle_player_board_1" ID="2aab1d9d-a150-436b-982c-da66f782a6d6" Version="2.3.2.3" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Node" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="exp_bg" ActionTag="-69790068" Tag="15" IconVisible="False" LeftMargin="-29.5000" RightMargin="-145.5000" TopMargin="13.6826" BottomMargin="-53.6826" Scale9Enable="True" LeftEage="16" RightEage="16" TopEage="16" BottomEage="16" Scale9OriginX="16" Scale9OriginY="16" Scale9Width="19" Scale9Height="19" ctype="ImageViewObjectData">
            <Size X="175.0000" Y="40.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="58.0000" Y="-33.6826" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="common/back_gray.png" Plist="textures/common.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="exp_bar_bg" ActionTag="-1521390273" Tag="13" IconVisible="False" LeftMargin="-21.0000" RightMargin="-139.0000" TopMargin="39.0000" BottomMargin="-49.0000" ctype="SpriteObjectData">
            <Size X="160.0000" Y="10.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="59.0000" Y="-44.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="battle/exp_bar.png" Plist="textures/battle.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="exp_bar" ActionTag="1879926722" Tag="14" IconVisible="False" LeftMargin="8.0000" RightMargin="-134.0000" TopMargin="42.0000" BottomMargin="-46.0000" ProgressInfo="20" ctype="LoadingBarObjectData">
            <Size X="126.0000" Y="4.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="71.0000" Y="-44.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <ImageFileData Type="PlistSubImage" Path="battle/exp_progress.png" Plist="textures/battle.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="board_bg" ActionTag="-786491580" Tag="3" IconVisible="False" LeftMargin="-150.0000" RightMargin="-150.0000" TopMargin="-40.0000" BottomMargin="-40.0000" Scale9Enable="True" LeftEage="16" RightEage="16" TopEage="16" BottomEage="16" Scale9OriginX="16" Scale9OriginY="16" Scale9Width="19" Scale9Height="19" ctype="ImageViewObjectData">
            <Size X="300.0000" Y="80.0000" />
            <Children>
              <AbstractNodeData Name="icon_gender" ActionTag="-1518966636" Tag="4" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="140.0000" RightMargin="150.0000" TopMargin="13.0000" BottomMargin="53.0000" ctype="SpriteObjectData">
                <Size X="10.0000" Y="14.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="145.0000" Y="60.0000" />
                <Scale ScaleX="1.2500" ScaleY="1.2500" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4833" Y="0.7500" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="common/icon_male.png" Plist="textures/common.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_state" ActionTag="-387411875" Tag="7" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="12.5000" RightMargin="262.5000" TopMargin="43.5000" BottomMargin="11.5000" ctype="SpriteObjectData">
                <Size X="25.0000" Y="25.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="25.0000" Y="24.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0833" Y="0.3000" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="common/icon_state_1.png" Plist="textures/common.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="hp_back" ActionTag="188667858" Tag="10" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="TopEdge" LeftMargin="150.5000" RightMargin="10.5000" TopMargin="38.5000" BottomMargin="28.5000" ctype="SpriteObjectData">
                <Size X="139.0000" Y="13.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="220.0000" Y="35.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7333" Y="0.4375" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="common/hp_back.png" Plist="textures/common.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="hp_bar" ActionTag="1519541676" Tag="11" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="TopEdge" LeftMargin="152.0000" RightMargin="12.0000" TopMargin="40.0000" BottomMargin="30.0000" ProgressInfo="100" ctype="LoadingBarObjectData">
                <Size X="136.0000" Y="10.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="220.0000" Y="35.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.7333" Y="0.4375" />
                <PreSize X="0.4533" Y="0.1000" />
                <ImageFileData Type="PlistSubImage" Path="common/hp_green.png" Plist="textures/common.plist" />
              </AbstractNodeData>
              <AbstractNodeData Name="pokemon_name" ActionTag="1262623502" Tag="3" IconVisible="False" VerticalEdge="TopEdge" LeftMargin="10.0000" RightMargin="168.0000" TopMargin="9.0000" BottomMargin="49.0000" FontSize="20" LabelText="我的名字很长" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="122.0000" Y="22.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="10.0000" Y="60.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.0333" Y="0.7500" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="fonts/DFPYuanW7-GB.ttf" Plist="" />
                <OutlineColor A="255" R="0" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="pokemon_lv" ActionTag="-408012991" Tag="8" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="TopEdge" LeftMargin="227.0000" RightMargin="15.0000" TopMargin="9.0000" BottomMargin="49.0000" FontSize="20" LabelText="Lv.100" HorizontalAlignmentType="HT_Right" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="58.0000" Y="22.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="285.0000" Y="60.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9500" Y="0.7500" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="fonts/DFPYuanW7-GB.ttf" Plist="" />
                <OutlineColor A="255" R="0" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="hp_info" ActionTag="528013667" Tag="12" IconVisible="False" HorizontalEdge="RightEdge" VerticalEdge="BottomEdge" LeftMargin="190.5000" RightMargin="12.5000" TopMargin="54.6826" BottomMargin="7.3174" FontSize="18" LabelText="9999 / 9999&#xA;" HorizontalAlignmentType="HT_Right" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="97.0000" Y="18.0000" />
                <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
                <Position X="287.5000" Y="16.3174" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.9583" Y="0.2040" />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="fonts/DFPYuanW7-GB.ttf" Plist="" />
                <OutlineColor A="255" R="0" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="hp_text" ActionTag="-368930699" Tag="26" IconVisible="False" LeftMargin="124.0000" RightMargin="154.0000" TopMargin="37.0000" BottomMargin="25.0000" FontSize="16" LabelText="HP" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="22.0000" Y="18.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="135.0000" Y="34.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition X="0.4500" Y="0.4250" />
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