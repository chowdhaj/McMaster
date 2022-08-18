module SvgAnimation exposing (..)

import Html as Html
import Platform.Cmd as Cmd
import Platform.Sub as Sub
import Svg exposing (..)
import Svg.Attributes exposing (..)
import AnimationFrame as Anim

{- Model
   Hold (x,y) coordinatees for a circle
 -}
type alias Model = {
        position : { x : Int, y : Int }
                   }

{- Wrap current Time as Float -}
type Msg = Tick Float

{- Define a starting position
   (ends up being irrelavent) -}
init = ({ position = {x = 300, y = 300}},Cmd.none)

{- Update
   Change position based on current time
 -}
update (Tick time) model = let
      posX = round <| 300 + 200 * cos (time/1000)
      posY = round <| 300 + 200 * sin (time/1000)
      modelN = { position = {x = posX, y = posY} }
    in (modelN,Cmd.none)

{- Subscriptions
   Subscribe to time using AnimationFrame for
   smooth rendering
 -}
subscriptions model = Anim.times Tick

{- View
   Render circle based on current position
   held in model
 -}
view : Model -> Html.Html Msg
view model = let
      posX = toString model.position.x
      posY = toString model.position.y
    in svg [width "600",height "600"]
       [circle [cx posX,cy posY, r "50", fill "red"] []]

{- Main -}
main : Program Never Model Msg
main = Html.program
       {init = init,
        update = update,
        view   = view,
        subscriptions = subscriptions }
