module KeyboardExample exposing (..)

import Html as Html
import Platform.Cmd as Cmd
import Platform.Sub as Sub
import Keyboard as Key

{- Model -}
type alias Model = { counter : Int }

init : (Model,Cmd.Cmd Msg)
init = ({ counter = 0 }, Cmd.none)

{- Update -}
type Msg = KeyMsg Key.KeyCode

{- Increment / Decrement counter with left and right keys -}
update : Msg -> Model -> (Model,Cmd.Cmd Msg)
update (KeyMsg keyCode)  model = case keyCode of
                        39 -> ({ model | counter = model.counter+1},Cmd.none)
                        37 -> ({ model | counter = model.counter-1},Cmd.none)
                        _ -> (model,Cmd.none)
{- View -}
view : Model -> Html.Html Msg
view model = Html.text (toString model.counter)

{- Subscriptions -}
subscriptions : Model -> Sub Msg
subscriptions model = Key.downs KeyMsg

{- Main -}
main : Program Never Model Msg
main = Html.program
          { init = init,
            view = view,
            update = update,
            subscriptions = subscriptions
            }

