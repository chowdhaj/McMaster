module MouseExample exposing (..)

import Html as Html
import Platform.Cmd as Cmd
import Platform.Sub as Sub
import Mouse as Mouse

{- Model -}
type alias Model = { position : (Int,Int) }

init : (Model,Cmd.Cmd Msg)
init = ({ position = (0,0) }, Cmd.none)

{- Update -}
type Msg = MouseMsg Mouse.Position

update : Msg -> Model -> (Model,Cmd.Cmd Msg)
update (MouseMsg pos) model = ({ position = (pos.x,pos.y) },Cmd.none)

{- View -}
view : Model -> Html.Html Msg
view model = Html.text (toString model.position)

{- Subscriptions -}
subscriptions : Model -> Sub Msg
subscriptions model =  Mouse.moves MouseMsg

{- Main -}
main : Program Never Model Msg
main = Html.program
          { init = init,
            view = view,
            update = update,
            subscriptions = subscriptions
            }

