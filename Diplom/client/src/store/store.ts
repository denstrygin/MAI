import {combineReducers, configureStore} from '@reduxjs/toolkit';
import mouseEventSlice from "./mouseEventReducer";
import questionEventSlice from './questionEventReducer';


const rootReducer = combineReducers({
    mouseEventSlice,
    questionEventSlice,
})

export function setupStore() {
    return configureStore({
        reducer: rootReducer
    })
}

export type RootState = ReturnType<typeof rootReducer>
export type AppStore = ReturnType<typeof setupStore>
export type AppDispatch = AppStore['dispatch']